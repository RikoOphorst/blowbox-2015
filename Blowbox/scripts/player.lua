Player = {}
Player.__index = Player

Player.new = function (x, y)
	local self = {}

	self.points = {}
	self.center = Game.verlet:addPoint(0, 0, 2)

	self.pointCount = 12

	local slice = 2 * math.pi / self.pointCount
	for i=0, self.pointCount, 1 do
		local angle = slice * i
		table.insert(self.points, Game.verlet:addPoint(math.sin(angle) * 150, math.cos(angle) * 150, 2))
	end

	for i=1, self.pointCount, 1 do
		local idx = i
		if (idx >= self.pointCount) then
			idx = 1
		else
			idx = idx + 1
		end
		
		self.points[i]:attachTo(self.points[idx], 10, 0.5, 0.2)
		self.points[i]:attachTo(self.center, 150, 0.95, 0)
	end

	local polypoints = {
		{self.center.pos.x, self.center.pos.y, 0}
	}
	local indices = {}

	for i, v in ipairs(self.points) do
		table.insert(polypoints, {
			v.pos.x,
			v.pos.y,
			0
		})
	end

	for i=1, self.pointCount, 1 do
		local idx = i + 1
		if (i == self.pointCount) then
			idx = 1
		end
		table.insert(indices, 0)
		table.insert(indices, i)
		table.insert(indices, idx)
	end

	self.polygon = Polygon.new(
		Game.RenderQueues.Default,
		polypoints,
		indices,
		Topology.TriangleList
	)

	setmetatable(self, Player)

	return self
end

function Player:update()
	self.polygon:setPoint(self.center.pos.x, self.center.pos.y, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0)

	for i=1, self.pointCount, 1 do
		self.polygon:setPoint(self.points[i].pos.x, self.points[i].pos.y, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, i)
	end
end