DistanceConstraint = {}
DistanceConstraint.__index = DistanceConstraint

DistanceConstraint.new = function (a, b, stiffness, distance)
	local self = {}

	self.a = a
	self.b = b

	self.stiffness = stiffness
	self.distance = distance or a.pos:sub(b.pos):length()

	setmetatable(self, DistanceConstraint)

	return self
end

function DistanceConstraint:relax(stepCoef)
	local normal = self.a.pos:sub(self.b.pos)
	local m = normal:lengthSq()

	normal:imul(((self.distance * self.distance - m)/m) * self.stiffness * stepCoef)

	self.a.pos:iadd(normal)

	self.b.pos:isub(normal)
end