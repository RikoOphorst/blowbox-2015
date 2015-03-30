require('./scripts/utility/console.lua')

require('./scripts/physics/verlet.lua')

Game.Initialise = function ()
	Game.Cameras = {
		Main = Camera.new(),
		UI = Camera.new()
	}

	Game.Cameras.Main:setMode(CameraModes.Orthographic)
	Game.Cameras.UI:setMode(CameraModes.Orthographic)

	RenderSettings.setResolution(640, 480)
	RenderSettings.setVSync(true)

	Game.RenderTargets = {
		Default = RenderTarget.new("default")
	}

	Game.RenderQueues = {
		Default = RenderQueue.new(Game.RenderTargets.Default)
	}

	Game.CreatePhysics()
end

Game.Update = function (dt)
	Game.dt = dt
	Game.elapsed = (Game.elapsed or 0) + dt

	for i, v in ipairs(Game.composite.particles) do
		local pos = Game.composite.particles[i].pos
		Game.polly:setPoint(pos.x, pos.y, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, i-1)
	end

	if (Keyboard.isPressed("Space")) then
		Game.simulate = not Game.simulate
	end

	local speed = 0.5

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

	Game.Physics = Verlet.new()

	Game.composite = Game.Physics:addBlob(Vector2D.new(0, -100), 50, 30, 0.3, 0.9)

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

	for i=1, 30, 1 do
		local idx = i + 1
		if (i == 30) then
			idx = 1
		end
		table.insert(indices, idx)
		table.insert(indices, i)
		table.insert(indices, #Game.composite.particles)
	end

	--print(#Game.composite.particles)

	indices = {
		1, 29, 30,
		2, 1, 30,
		3, 2, 30,
		4, 3, 30,
		5, 4, 30,
		6, 5, 30,
		7, 6, 30,
		8, 7, 30,
		9, 8, 30,
		10, 9, 30,
		11, 10, 30,
		12, 11, 30,
		13, 12, 30,
		14, 13, 30,
		15, 14, 30,
		16, 15, 30,
		17, 16, 30,
		18, 17, 30,
		19, 18, 30,
		20, 19, 30,
		21, 20, 30,
		22, 21, 30,
		23, 22, 30,
		24, 23, 30,
		25, 24, 30,
		26, 25, 30,
		27, 26, 30,
		28, 27, 30,
		29, 28, 30
	}

	for i, v in ipairs(vertices) do
		print (i .. ": " .. vertices[i][1] .. ", " .. vertices[i][2] .. ", ".. vertices[i][3])
	end

	Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
end 