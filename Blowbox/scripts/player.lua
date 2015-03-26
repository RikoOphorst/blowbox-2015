Player = {}
Player.__index = Player

Player.new = function (x, y)
	local self = {}

	self.points = {
		Game.verlet:addPoint(320, 0, 0.1),
		Game.verlet:addPoint(-320, 0, 0.1),
		Game.verlet:addPoint(-160, -160, 0.1)
	}

	self.points[1]:attachTo(self.points[2], 75, 0.02, 1)
	self.points[1]:attachTo(self.points[3], 75, 0.02, 1)
	self.points[2]:attachTo(self.points[3], 75, 0.02, 1)

	self.polygon = Polygon.new(
		Game.RenderQueues.Default,
		{
			{ self.points[1].pos.x, self.points[1].pos.y, 0 },
			{ self.points[2].pos.x, self.points[2].pos.y, 0 },
			{ self.points[3].pos.x, self.points[3].pos.y, 0 }
		},
		{
			2, 1, 0, 0, 1, 2
		},
		Topology.TriangleList
	)

	setmetatable(self, Player)

	return self
end

function Player:update()
	self.polygon:setPoint(self.points[1].pos.x, self.points[1].pos.y, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0)
	self.polygon:setPoint(self.points[2].pos.x, self.points[2].pos.y, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1)
	self.polygon:setPoint(self.points[3].pos.x, self.points[3].pos.y, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 2)
end