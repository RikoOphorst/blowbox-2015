Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.camera = Camera.new()
	Game.camera:setMode(CameraModes.Orthographic)

	Game.rendertarget = RenderTarget.new("default")
	Game.renderqueue = RenderQueue.new(Game.rendertarget)

	RenderSettings.setResolution(640, 480)

	Game.polly = Polygon.new(
		Game.renderqueue,
		{
			{ -1, 10, 1 },
			{ 0, -1, 1 },
			{ 1, 1, 1 }
		},
		{
			2, 1, 0
		},
		Topology.TriangleList
	);

	Game.polly:setScale(100, 100, 100)
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1

	Game.polly:setRotation2D(Game.t / 500)
end

Game.Draw = function ()
	Game.Render(Game.camera)
end
