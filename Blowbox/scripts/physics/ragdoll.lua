Ragdoll = {}
Ragdoll.__index = Ragdoll

Ragdoll.new = function (queue, origin, bodysize)
	local self = {}

	self.origin = origin
	self.bodysize = bodysize

	self.composite = Composite.new()

	local headLength = self.bodysize / 7.5;
	local headWidth = headLength * 3/4;

	self.particles = {}
	self.particles.head = Particle.new(origin.x + random() * 5, origin.y - random() * 5);
	self.particles.shoulder = Particle.new(origin.x + random() * 5, origin.y + random() * 5);
	self.particles.elbowLeft = Particle.new(origin.x - random() * 5, origin.y + random() * 5);
	self.particles.elbowRight = Particle.new(origin.x + random() * 5, origin.y + random() * 5);
	self.particles.handLeft = Particle.new(origin.x - random() * 5, origin.y + random() * 5);
	self.particles.handRight = Particle.new(origin.x + random() * 5, origin.y + random() * 5);
	self.particles.pelvis = Particle.new(origin.x + random() * 5, origin.y + random() * 5);
	self.particles.kneeLeft = Particle.new(origin.x - random() * 5, origin.y + random() * 5);
	self.particles.kneeRight = Particle.new(origin.x + random() * 5, origin.y + random() * 5);
	self.particles.footLeft = Particle.new(origin.x - random() * 5, origin.y + random() * 5);
	self.particles.footRight = Particle.new(origin.x + random() * 5, origin.y + random() * 5);

	table.insert(self.composite.particles, self.particles.head)
	table.insert(self.composite.particles, self.particles.shoulder)
	table.insert(self.composite.particles, self.particles.elbowLeft)
	table.insert(self.composite.particles, self.particles.elbowRight)
	table.insert(self.composite.particles, self.particles.handLeft)
	table.insert(self.composite.particles, self.particles.handRight)
	table.insert(self.composite.particles, self.particles.pelvis)
	table.insert(self.composite.particles, self.particles.kneeLeft)
	table.insert(self.composite.particles, self.particles.kneeRight)
	table.insert(self.composite.particles, self.particles.footLeft)
	table.insert(self.composite.particles, self.particles.footRight)

	local constraint

	-- SHOULDER
	constraint = DistanceConstraint.new(self.particles.head, self.particles.shoulder, 1, 0, 5/4 * headLength)
	table.insert(self.composite.constraints, constraint)

	-- ELBOWS --
	constraint = DistanceConstraint.new(self.particles.elbowLeft, self.particles.shoulder, 1, 0, headLength*3/2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.elbowRight, self.particles.shoulder, 1, 0, headLength*3/2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.elbowLeft, self.particles.head, 0.01, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.elbowRight, self.particles.head, 0.01, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	-- HANDS --
	constraint = DistanceConstraint.new(self.particles.handLeft, self.particles.elbowLeft, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.handRight, self.particles.elbowRight, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.handLeft, self.particles.handRight, 0.01, 0, headLength*4)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.handLeft, self.particles.head, 0.01, 0, headLength*3)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.handRight, self.particles.head, 0.01, 0, headLength*3)
	table.insert(self.composite.constraints, constraint)

	-- PELVIS
	constraint = DistanceConstraint.new(self.particles.pelvis, self.particles.shoulder, 1, 0, headLength*3.5)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.pelvis, self.particles.head, 1, 0, headLength*4.75)
	table.insert(self.composite.constraints, constraint)

	-- KNEES --
	constraint = DistanceConstraint.new(self.particles.kneeLeft, self.particles.pelvis, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.kneeRight, self.particles.pelvis, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	-- FEET --
	constraint = DistanceConstraint.new(self.particles.footLeft, self.particles.kneeLeft, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.footRight, self.particles.kneeRight, 1, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.footLeft, self.particles.shoulder, 0.001, 0, headLength*7.5)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.footRight, self.particles.shoulder, 0.001, 0, headLength*7.5)
	table.insert(self.composite.constraints, constraint)

	constraint = DistanceConstraint.new(self.particles.footLeft, self.particles.footRight, 0.01, 0, headLength*2)
	table.insert(self.composite.constraints, constraint)

	setmetatable(self, Ragdoll)

	self.parts = {}
	self.parts.head = Quad.new(queue)
	self.parts.torso = Quad.new(queue)
	self.parts.armLeft = Quad.new(queue)
	self.parts.armRight = Quad.new(queue)
	self.parts.legLeft = Quad.new(queue)
	self.parts.legRight = Quad.new(queue)

	self.parts.head:setTexture('./textures/lenna.png')

	return self
end

function Ragdoll:update()
	self.parts.head:setScale2D(self.particles.head.pos:distance(self.particles.shoulder.pos), self.particles.head.pos:distance(self.particles.shoulder.pos))
	self.parts.head:setRotation2D(math.atan2(self.particles.head.pos.y - self.particles.shoulder.pos.y, self.particles.head.pos.x - self.particles.shoulder.pos.x) + math.pi / 2)
	self.parts.head:setPosition2D(self.particles.head.pos.x, self.particles.head.pos.y)

	self.parts.torso:setScale2D(5, self.particles.shoulder.pos:distance(self.particles.pelvis.pos))
	self.parts.torso:setRotation2D(math.atan2(self.particles.shoulder.pos.y - self.particles.pelvis.pos.y, self.particles.shoulder.pos.x - self.particles.pelvis.pos.x) + math.pi / 2)
	self.parts.torso:setPosition2D(self.particles.shoulder.pos.x, self.particles.shoulder.pos.y)
	self.parts.torso:setOffset2D(0, 0.5)

	self.parts.armLeft:setScale2D(5, self.particles.shoulder.pos:distance(self.particles.handLeft.pos))
	self.parts.armLeft:setRotation2D(math.atan2(self.particles.shoulder.pos.y - self.particles.handLeft.pos.y, self.particles.shoulder.pos.x - self.particles.handLeft.pos.x) + math.pi / 2)
	self.parts.armLeft:setPosition2D(self.particles.shoulder.pos.x, self.particles.shoulder.pos.y)
	self.parts.armLeft:setOffset2D(0, 0.5)

	self.parts.armRight:setScale2D(5, self.particles.shoulder.pos:distance(self.particles.handRight.pos))
	self.parts.armRight:setRotation2D(math.atan2(self.particles.shoulder.pos.y - self.particles.handRight.pos.y, self.particles.shoulder.pos.x - self.particles.handRight.pos.x) + math.pi / 2)
	self.parts.armRight:setPosition2D(self.particles.shoulder.pos.x, self.particles.shoulder.pos.y)
	self.parts.armRight:setOffset2D(0, 0.5)

	self.parts.legLeft:setScale2D(5, self.particles.pelvis.pos:distance(self.particles.footLeft.pos))
	self.parts.legLeft:setRotation2D(math.atan2(self.particles.pelvis.pos.y - self.particles.footLeft.pos.y, self.particles.pelvis.pos.x - self.particles.footLeft.pos.x) + math.pi / 2)
	self.parts.legLeft:setPosition2D(self.particles.pelvis.pos.x, self.particles.pelvis.pos.y)
	self.parts.legLeft:setOffset2D(0, 0.5)

	self.parts.legRight:setScale2D(5, self.particles.pelvis.pos:distance(self.particles.footRight.pos))
	self.parts.legRight:setRotation2D(math.atan2(self.particles.pelvis.pos.y - self.particles.footRight.pos.y, self.particles.pelvis.pos.x - self.particles.footRight.pos.x) + math.pi / 2)
	self.parts.legRight:setPosition2D(self.particles.pelvis.pos.x, self.particles.pelvis.pos.y)
	self.parts.legRight:setOffset2D(0, 0.5)
end