Particle = {}
Particle.__index = Particle

Particle.new = function (x, y)
	local self = {}

	self.pos = Vector2D.new(x, y)
	self.lastPos = Vector2D.new(x, y)

	setmetatable(self, Particle)

	return self
end
