DistanceConstraint = {}
DistanceConstraint.__index = DistanceConstraint

DistanceConstraint.new = function (a, b, stiffness, tearDistance, distance)
	local self = {}

	self.a = a
	self.b = b

	self.stiffness = stiffness
	self.distance = distance or a.pos:sub(b.pos):length()
	self.tearDistance = tearDistance or self.distance * 2

	setmetatable(self, DistanceConstraint)

	return self
end

function DistanceConstraint:relax(stepCoef)
	if (self.a.pos:distance(self.b.pos) > self.tearDistance) then
		--return false
	end

	local normal = self.a.pos:sub(self.b.pos)
	local m = normal:lengthSq()

	normal:imul(((self.distance * self.distance - m)/m) * self.stiffness * stepCoef)

	self.a.pos:iadd(normal)

	self.b.pos:isub(normal)

	return true
end