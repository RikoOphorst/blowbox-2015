Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.camera = Camera.new()
	Game.camera:setMode(CameraModes.Orthographic)

	Game.rendertarget = RenderTarget.new("default")
	Game.rendertarget2 = RenderTarget.new("rt")
	Game.renderqueue = RenderQueue.new(Game.rendertarget)
	Game.renderqueue2 = RenderQueue.new(Game.rendertarget2)

	Game.quad = Quad.new(Game.renderqueue)
	Game.quad2 = Quad.new(Game.renderqueue2)
	Game.quad:setPosition2D(-280, -200)
	Game.quad2:setPosition2D(0, 0)

	Game.quad:setScale2D(50, 50)
	Game.quad2:setScale2D(50, 50)

	RenderSettings.setResolution(640, 480)
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1
end

Game.Draw = function ()
	Game.Render(Game.camera)
end
