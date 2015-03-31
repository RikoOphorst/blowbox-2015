Composite = {}
Composite.__index = Composite

Composite.new = function ()
	local self = {}

	self.particles = {}
	self.constraints = {}

	setmetatable(self, Composite)

	return self
end

function Composite:pin(index, pos)
	pos = pos or self.particles[index].pos
	local pc = PinConstraint.new(self.particles[index], pos)
	table.insert(self.constraints, pc)

	return pc
end