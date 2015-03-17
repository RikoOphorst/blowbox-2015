Game.Initialise = function ()
	Game.camera = Camera.new()
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1

	if (Game.t == 300) then
		rendertarget:setQueue(renderqueue)
	end
end

Game.Draw = function ()
	Game.Render(Game.camera)
end

rendertarget = RenderTarget.new("default")
renderqueue = RenderQueue.new(rendertarget)

anotherqueue = RenderQueue.new(rendertarget)

quaderino = Quad.new(renderqueue)
quad2 = Quad.new(anotherqueue)

quaderino:setScale2D(50, 50)
quad2:setScale2D(75, 75)