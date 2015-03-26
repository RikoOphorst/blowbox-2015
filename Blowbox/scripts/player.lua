Player = {}
Player.__index = Player

Player.new = function (x, y)
	local self = {}

	self.quad1 = Quad.new(Game.RenderQueues.Default)
	self.quad2 = Quad.new(Game.RenderQueues.Default)

	self.points = {
		VerletPoint.new(320, 50),
		VerletPoint.new(-320, -50)
	}

	self.points[2].vel.y = -self.points[2].vel.y
	self.points[2].acc.y = -self.points[2].acc.y

	self.constraint = LinkConstraint.new(self.points[1], self.points[2], 200)

	self.quad1:setScale2D(10, 10)
	self.quad2:setScale2D(10, 10)

	setmetatable(self, Player)

	return self
end

function Player:update()

	self.constraint:solve()

	for k, v in ipairs(self.points) do
		v:update()
	end

	self.quad1:setPosition2D(self.points[1].pos.x, self.points[1].pos.y)
	self.quad2:setPosition2D(self.points[2].pos.x, self.points[2].pos.y)
end