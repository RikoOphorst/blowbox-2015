Game.Initialise = function ()
	ContentManager.loadTexture("Lenna.png")

	Game.cameras = {
		main = Camera.new(),
		ui = Camera.new()
	}

	Game.cameras.main:setMode(CameraModes.Orthographic)
	Game.cameras.ui:setMode(CameraModes.Orthographic)

	RenderSettings.setResolution(640, 480)
	RenderSettings.setVSync(true)

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

	Game.widget = Widget.new(Game.renderqueue)
	Game.widget:setScale2D(75, 75)
	Game.widget:setPosition2D(280, 200)
end

Game.Update = function (dt)
	Game.t = Game.t or 0

	Game.t = Game.t + 1

	if (Keyboard.isDown("W")) then
		local x, y = Game.quad:getPosition2D()
		Game.quad:setPosition2D(x, y - 1)
	end
	if (Keyboard.isDown("A")) then
		local x, y = Game.quad:getPosition2D()
		Game.quad:setPosition2D(x - 1, y)
	end
	if (Keyboard.isDown("S")) then
		local x, y = Game.quad:getPosition2D()
		Game.quad:setPosition2D(x, y + 1)
	end
	if (Keyboard.isDown("D")) then
		local x, y = Game.quad:getPosition2D()
		Game.quad:setPosition2D(x + 1, y)
	end

	Game.cameras.main:setPosition(math.sin(Game.t / 5) * 50, math.cos(Game.t/ 5) * 50, -10)
	Game.cameras.main:setTarget(math.sin(Game.t / 5) * 50, math.cos(Game.t/ 5) * 50, -9)
end

Game.Draw = function ()
	Game.Render(Game.cameras.main, Game.cameras.ui)
end
