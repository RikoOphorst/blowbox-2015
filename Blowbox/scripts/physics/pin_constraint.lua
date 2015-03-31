PinConstraint = {}
PinConstraint.__index = PinConstraint

PinConstraint.new = function (a, pos)
	local self = {}

	self.a = a
	self.pos = Vector2D.new(pos.x, pos.y)
	self.type = 'pin'

	setmetatable(self, PinConstraint)

	return self
end

function PinConstraint:relax(stepCoef)
	self.a.pos.x = self.pos.x
	self.a.pos.y = self.pos.y
end