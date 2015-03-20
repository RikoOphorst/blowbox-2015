Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.camera = Camera.new()
	Game.camera:setMode(CameraModes.Orthographic)

	Game.rendertarget = RenderTarget.new("default")
	Game.renderqueue = RenderQueue.new(Game.rendertarget)

	Game.cube = Quad.new(Game.renderqueue)
	Game.cube:setPosition(30, 0, 0)
	Game.cube:setScale(10, 10, 10)
	Game.cube:setTexture("Lenna.png")

	RenderSettings.setResolution(640, 480)
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1
	Game.cube:setScale(500, 500, 10)
	Game.cube:setPosition(0, 0, 0)
end

Game.Draw = function ()
	Game.Render(Game.camera)
end
