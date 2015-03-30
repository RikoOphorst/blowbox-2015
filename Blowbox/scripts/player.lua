Player = {}
Player.__index = Player

Player.new = function (x, y)
	local self = {}

	self.quad = Quad.new(Game.RenderQueues.Default)
	self.pos = Vector2D.new(x, y)
	self.velocity = Vector2D.new(0, 0)

	self.quad:setScale2D(200, 200)

	setmetatable(self, Player)

	return self
end

function Player:update()
	self.pos:iadd(self.velocity)

	self.quad.setPosition2D(self.pos.x, self.pos.y)
end