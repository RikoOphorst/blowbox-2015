Player = class(Quad, function (this, queue, x, y) 
	this.pos = Vector2D.new(x, y)

	this.velocity = Vector2D.new(0, 0)

	this:setScale2D(50, 50)
end)

function Player:update(timesteps, step)
	self.pos:iadd(self.velocity:mul(16))

	self:setPosition2D(self.pos.x, self.pos.y)
end