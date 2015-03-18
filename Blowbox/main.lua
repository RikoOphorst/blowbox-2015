Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.camera = Camera.new()
	Game.camera:setMode(CameraModes.Perspective)

	Game.rendertarget = RenderTarget.new("default")
	Game.renderqueue = RenderQueue.new(Game.rendertarget)

	Game.cube = Cube.new(Game.renderqueue)
	Game.cube:setPosition(30, 0, 0)
	Game.cube:setScale(10, 10, 10)
	Game.cube:setTexture("Lenna.png")
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1
	Game.cube:setPosition(math.sin(Game.t / 10000) * 25, 0, 0)
	Game.cube:setRotation(Game.t / 5000, Game.t / 2500, 0)
end

Game.Draw = function ()
	Game.Render(Game.camera)
end
