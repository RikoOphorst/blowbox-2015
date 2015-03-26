require("./scripts/verletpoint.lua")
require("./scripts/linkconstraint.lua")
require("./scripts/utility/array.lua")

Verlet = {}
Verlet.__index = Verlet

Verlet.new = function ()
	local self = {}

	self.points = {}

	self.gravity = Vector2D.new(0, 0.1)

	setmetatable(self, Verlet)
	return self
end

function Verlet:update()
	for i, v in ipairs (self.points) do
		v:solveConstraints()

		v:update(self.gravity)
	end
end

function Verlet:addPoint(x, y, acc)
	local point = VerletPoint.new(x, y, acc)

	table.insert(self.points, point)

	return point
end