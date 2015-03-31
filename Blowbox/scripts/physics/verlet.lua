require('./scripts/math/vector.lua')
require('./scripts/physics/particle.lua')
require('./scripts/physics/composite.lua')
require('./scripts/physics/pin_constraint.lua')
require('./scripts/physics/distance_constraint.lua')

Verlet = {}
Verlet.__index = Verlet

Verlet.new = function ()
	local self = {}

	self.composites = {}

	self.gravity = Vector2D.new(0, 0.2)
	self.friction = 0.99
	self.groundFriction = 0.8

	setmetatable(self, Verlet)

	return self
end

function Verlet:update(step)
	-- loop through all registered composites
	for i, v in ipairs (self.composites) do

		-- cache its particles
		local particles = self.composites[i].particles;

		-- loop through all the particles of the current composite
		for j, w in ipairs (particles) do
			local particle = particles[j]

			local velocity = particle.pos:sub(particle.lastPos):mul(self.friction)

			-- implement ground friction here

			-- save last state
			particle.lastPos = Vector2D.new(particle.pos.x, particle.pos.y)

			-- gravity
			particle.pos:iadd(self.gravity)

			-- inertia
			particle.pos:iadd(velocity)
		end
	end

	-- implement mouse interaction here

	-- relaxation
	local stepCoef = 1/step
	for i, v in ipairs(self.composites) do
		local constraints = self.composites[i].constraints

		for a = 0, step, 1 do
			for j, w in ipairs(constraints) do
				constraints[j]:relax(stepCoef)
			end
		end
	end

	-- bounds
	for i, v in ipairs(self.composites) do
		local particles = self.composites[i].particles

		for j, w in ipairs(particles) do
			self:bounds(particles[j])
		end
	end
end

function Verlet:getNearestParticle(point)
	local d2Nearest = 0
	local nearest
	local selectionRadius = 20
	local nearestConstraints = {}

	for i, v in ipairs(self.composites) do
		local particles = self.composites[i].particles

		for j, w in ipairs(particles) do
			local d2 = particles[j].pos:distanceSq(point)
			if (d2 <= selectionRadius^2 and (nearest == nil or d2 < d2Nearest)) then
				nearest = particles[j]
				nearestConstraints = self.composites[i].constraints
				d2Nearest = d2
			end
		end
	end

	for i, v in ipairs(nearestConstraints) do
		if (nearestConstraints[i].type == 'pin' and nearestConstraints[i].a == nearest) then
			nearest = nearestConstraints[i]
		end
	end

	return nearest
end

function Verlet:bounds(particle)
	if (particle.pos.y > 305-1) then
		particle.pos.y = 305-1
	end
	
	if (particle.pos.x < -445) then
		particle.pos.x = -445
	end

	if (particle.pos.x > 265) then
		particle.pos.x = 265
	end
end

function Verlet:addComposite(vertices, stiffness)
	local composite = Composite.new()

	for i, v in ipairs(vertices) do
		table.insert(composite.particles, Particle.new(vertices[i].x, vertices[i].y))

		if (i > 1) then
			table.insert(composite.constraints, DistanceConstraint.new(composite.particles[i], composite.particles[i - 1], stiffness))
		end
	end

	table.insert(self.composites, composite)
	return composite
end

function Verlet:removeComposite()

end

function Verlet:addBlob(origin, radius, segments, spokeStiffness, treadStiffness)
	local stride = (2*math.pi)/segments
	
	local composite = Composite.new()
	
	for i=0, segments - 1, 1 do
		local theta = i*stride
		table.insert(composite.particles, Particle.new(origin.x + math.cos(theta)*radius, origin.y + math.sin(theta)*radius))
	end
	
	local center = Particle.new(origin.x, origin.y)
	table.insert(composite.particles, center)
	
	local chance = math.random()

	for i=0, segments - 1, 1 do
		if (chance > 0.001) then
			table.insert(composite.constraints, DistanceConstraint.new(composite.particles[i+1], composite.particles[math.fmod(i+1, segments)+1], treadStiffness))
		end
		table.insert(composite.constraints, DistanceConstraint.new(composite.particles[i+1], center, spokeStiffness))
		table.insert(composite.constraints, DistanceConstraint.new(composite.particles[i+1], composite.particles[math.fmod(i+5, segments)+1], treadStiffness))
	end
		
	table.insert(self.composites, composite)
	return composite
end

function Verlet:addCloth(origin, width, height, segments, pinMod, stiffness)
	local composite = Composite.new()
	
	local xStride = width/segments
	local yStride = height/segments
	
	for y=0, segments, 1 do
		for x=0, segments - 1, 1 do
			local px = origin.x + x*xStride - width/2 + xStride/2
			local py = origin.y + y*yStride - height/2 + yStride/2
			table.insert(composite.particles, Particle.new(px, py))
			
			if (x > 0) then
				table.insert(
					composite.constraints, 
					DistanceConstraint.new(
						composite.particles[(y*segments+x)+1], 
						composite.particles[(y*segments+x-1)+1], 
						stiffness
					)
				)
			end
			
			if (y > 0) then
				table.insert(
					composite.constraints, 
					DistanceConstraint.new(
						composite.particles[(y*segments+x)+1], 
						composite.particles[((y-1)*segments+x)+1], 
						stiffness
					)
				)
			end
		end
	end
	
	for x=0, segments, 1 do
		if (math.fmod(x, pinMod) == 0) then
			composite:pin(x+1)
		end
	end
	
	table.insert(self.composites, composite)
	return composite
end