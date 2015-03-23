Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.camera = Camera.new()
	Game.camera:setMode(CameraModes.Orthographic)

	Game.rendertarget = RenderTarget.new("default")
	Game.renderqueue = RenderQueue.new(Game.rendertarget)

	RenderSettings.setResolution(640, 480)
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1
end

Game.Draw = function ()
	Game.Render(Game.camera)
end
