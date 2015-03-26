VerletPoint = {}
VerletPoint.__index = VerletPoint

VerletPoint.new = function (x, y, mass)
	local self = {}

	self.pos = Vector2D.new(x, y)
	self.lastpos = Vector2D.new(x, y)

	self.mass = mass or 1

	self.vel = Vector2D.new(0, 0)
	self.acc = Vector2D.new(0, 0)

	self.links = {}

	setmetatable(self, VerletPoint)

	return self
end

function VerletPoint:update(gravity)
	self:applyForce(gravity:mul(self.mass))

	self.vel = self.pos:sub(self.lastpos)
	self.vel:imul(0.99)

	self.lastpos = Vector2D.new(self.pos.x, self.pos.y)

	self.pos = self.pos:add(self.vel):add(self.acc)

	self.acc.x = 0
	self.acc.y = 0
end

function VerletPoint:solveConstraints()
	for i, v in ipairs(self.links) do
		v:solve()
	end

	local height = 640
	local width = 480

	if (self.pos.y < -240) then
      	self.pos.y = 2 * (-240) - self.pos.y;
  	end

    if (self.pos.y > 200) then
      	self.pos.y = 2 * (200) - self.pos.y;
  	end
      
    if (self.pos.x > 320) then
		self.pos.x = 2 * (320) - self.pos.x;
    end

    if (self.pos.x < -320) then 
      	self.pos.x = 2 * (-320) - self.pos.x;
    end
end

function VerletPoint:attachTo(other, restingDistance, stiffness, tearSensitivity)
	table.insert(self.links, LinkConstraint.new(self, other, restingDistance, stiffness, tearSensitivity))
	return #self.links
end

function VerletPoint:removeLink(pos)
	table.remove(self.table, pos)
end

function VerletPoint:applyForce(force)
	self.acc:iadd(force:div(self.mass))
end