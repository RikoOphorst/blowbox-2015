require('./scripts/utility/console.lua')

require('./scripts/physics/verlet.lua')

require('./scripts/ui/button.lua')

math.randomseed(os.time())

Game.Initialise = function ()
	Game.Cameras = {
		Main = Camera.new(),
		UI = Camera.new()
	}

	Game.Cameras.Main:setMode(CameraModes.Orthographic)
	Game.Cameras.UI:setMode(CameraModes.Orthographic)

	RenderSettings.setResolution(1024, 720)
	RenderSettings.setVSync(true)

	Game.RenderTargets = {
		Default = RenderTarget.new("default")
	}

	Game.RenderQueues = {
		Default = RenderQueue.new(Game.RenderTargets.Default)
	}

	ContentManager.loadTexture('./textures/background.png')
	ContentManager.loadTexture('./textures/highlighter.png')
	ContentManager.loadTexture('./textures/reset.png')
	ContentManager.loadTexture('./textures/reset_up.png')
	ContentManager.loadTexture('./textures/play.png')
	ContentManager.loadTexture('./textures/pause.png')
	ContentManager.loadShader('./shaders/blob.fx')

	Game.Background = Quad.new(Game.RenderQueues.Default)
	Game.Background:setScale2D(1024, 720)
	Game.Background:setTexture('./textures/background.png')
	Game.Background:setPosition(0, 0, -1)

	Game.highlighter = Widget.new(Game.RenderQueues.Default)
	Game.highlighter:setAlpha(0)
	Game.highlighter:setScale2D(20, 20)
	Game.highlighter:setTexture('./textures/highlighter.png')
	Game.highlighter:setPosition(0, 0, 5)

	Game.resetBtn = Button.new(Game.RenderQueues.Default, 298, -337, 200, 75, './textures/reset.png')
	function Game.resetBtn:onHoverIn()
		Game.resetBtn.widget:setTexture('./textures/reset_up.png')
	end
	function Game.resetBtn:onDown()
		Game.resetBtn.widget:setTexture('./textures/reset_up.png')

		Game.CreatePhysics()
	end
	function Game.resetBtn:onHoverOut()
		Game.resetBtn.widget:setTexture('./textures/reset.png')
	end
	function Game.resetBtn:onUp()
		Game.resetBtn.widget:setTexture('./textures/reset.png')
	end

	Game.playpause = Widget.new(Game.RenderQueues.Default)
	Game.playpause:setAlpha(0)
	Game.playpause:setTexture('./textures/play.png')
	Game.playpause:setScale2D(150, 150)

	Game.Mode = "cloth"

	Game.CreatePhysics()
end

Game.Update = function (dt)
	Game.dt = dt
	Game.elapsed = (Game.elapsed or 0) + dt

	local mx, my = Mouse.getPosition()
	local mousePos = { x = mx - (1024/2), y = my - (720/2) }
	Game.resetBtn:update(mousePos)

	for i, v in ipairs(Game.composite.particles) do
		local pos = Game.composite.particles[i].pos
		if (i - 1 ~= #Game.composite.particles - 1) then
			Game.polly:setPoint(pos.x, pos.y, 0, 0, 0.5, 0, 1, 0, 0, 0, 0, 0, i-1)
		else
			Game.polly:setPoint(pos.x, pos.y, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, i-1)
		end
	end

	if (Keyboard.isPressed("Space")) then
		Game.simulate = not Game.simulate

		Game.playpause:setAlpha(1)

		if (Game.simulate) then
			Game.playpause:setTexture('./textures/play.png')
		else
			Game.playpause:setTexture('./textures/pause.png')
		end
	end

	if (Game.playpause:getAlpha() > 0) then
		Game.playpause:setAlpha(Game.playpause:getAlpha() - 0.04)
	end

	local speed = 0.5


	if (Game.simulate) then
		if (Keyboard.isDown("W")) then
			for i, v in ipairs(Game.composite.particles) do
				Game.composite.particles[i].pos.y = Game.composite.particles[i].pos.y - speed
			end
		end

		if (Keyboard.isDown("A")) then
			for i, v in ipairs(Game.composite.particles) do
				Game.composite.particles[i].pos.x = Game.composite.particles[i].pos.x - speed
			end
		end

		if (Keyboard.isDown("S")) then
			for i, v in ipairs(Game.composite.particles) do
				Game.composite.particles[i].pos.y = Game.composite.particles[i].pos.y + speed
			end
		end

		if (Keyboard.isDown("D")) then
			for i, v in ipairs(Game.composite.particles) do
				Game.composite.particles[i].pos.x = Game.composite.particles[i].pos.x + speed
			end
		end
	end

	local particle = Game.Physics:getNearestParticle(mousePos)

	if (particle ~= nil) then
		Game.highlighter:setAlpha(1)
		Game.highlighter:setPosition(particle.pos.x, particle.pos.y, 5)

		if (Mouse.isDown("left")) then
			Game.selectedParticle = particle
		end
	else
		Game.highlighter:setAlpha(0)
	end

	if (Game.selectedParticle ~= nil) then
		if (not Mouse.isDown("left")) then
			Game.selectedParticle = nil
		else
			Game.selectedParticle.pos.x = mousePos.x
			Game.selectedParticle.pos.y = mousePos.y
		end
	end
end

Game.FixedUpdate = function(timesteps, step)
	if (Game.simulate) then
		Game.Physics:update(step)
	end
end

Game.Draw = function ()
	Game.Render(Game.Cameras.Main, Game.Cameras.UI)
end

Game.OnReload = function (path)
	--Game.CreatePhysics()
end

Game.CreatePhysics = function ()
	Game.simulate = false
	Game.playpause:setTexture('./textures/pause.png')
	Game.playpause:setAlpha(1)

	Game.Physics = Verlet.new()

	if (Game.Mode == "blob") then
		local segments = 40

		Game.composite = Game.Physics:addBlob(Vector2D.new(-89, -100), 100, segments, 0.1, 0.7)

		local vertices = {}
		local indices = {}

		for i, v in ipairs(Game.composite.particles) do
			local vert = {
				Game.composite.particles[i].pos.x,
				Game.composite.particles[i].pos.y,
				0
			}

			table.insert(vertices, vert)
		end

		for i=1, segments, 1 do
			local idx = i + 1
			if (i == segments - 1) then
				idx = 1
			end
			table.insert(indices, idx)
			table.insert(indices, i)
			table.insert(indices, #Game.composite.particles - 1)
		end

		Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
		Game.polly:setShader('./shaders/blob.fx')
	end

	if (Game.Mode == "cloth") then
		local origin = Vector2D.new(-89, -100)
		local width = 200
		local height = 200
		local segments = 20
		local pinMod = 4
		local stiffness = 0.1

		Game.composite = Game.Physics:addCloth(origin, width, height, segments, pinMod, stiffness)

		local vertices = {}
		local indices = {}

		for i, v in ipairs(Game.composite.particles) do
			local vert = {
				Game.composite.particles[i].pos.x,
				Game.composite.particles[i].pos.y,
				0
			}

			table.insert(vertices, vert)
		end

		for y=0, segments - 1, 1 do
			for x=0, segments - 2, 1 do
				table.insert(indices, y*segments+x)
				table.insert(indices, (y+1)*segments+x)
				table.insert(indices, (y+1)*segments+x+1)
				table.insert(indices, (y+1)*segments+x+1)
				table.insert(indices, y*segments+x+1)
				table.insert(indices, y*segments+x)
			end
		end

		Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
	end
end