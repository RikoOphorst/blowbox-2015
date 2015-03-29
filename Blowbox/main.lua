require("./scripts/utility/class.lua")
require("./scripts/math/vector.lua")
require("./scripts/player.lua")
require("./scripts/verlet.lua")

-- Hacky sack solution
if (printCache == nil) then
	printCache = print
	print = function (string)
		printCache(tostring(string))
	end
end
-- Hacky sack solution


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

	ContentManager.loadTexture("./textures/lenna.png")

	Game.verlet = Verlet.new()

	Game.player = Player.new(-50, -50)

	Game.simulate = false
end

Game.Update = function (dt)
	Game.dt = dt
	Game.elapsed = (Game.elapsed or 0) + dt

	Game.player:update(dt)

	if (Keyboard.isPressed("E")) then
		Game.simulate = not Game.simulate
	end

	local speed = 0.5

	if (Keyboard.isDown("W")) then
		for i,v in ipairs(Game.player.points) do
			v:applyForce(Vector2D.new(0, -speed))
		end
	end

	if (Keyboard.isDown("A")) then
		for i,v in ipairs(Game.player.points) do
			v:applyForce(Vector2D.new(-speed, 0))
		end
	end

	if (Keyboard.isDown("S")) then
		for i,v in ipairs(Game.player.points) do
			v:applyForce(Vector2D.new(0, speed))
		end
	end

	if (Keyboard.isDown("D")) then
		for i,v in ipairs(Game.player.points) do
			v:applyForce(Vector2D.new(speed, 0))
		end
	end
end

Game.FixedUpdate = function(timesteps, step)
	if (Game.simulate == true) then 
		Game.verlet:update(timesteps, step)
	end
end

Game.Draw = function ()
	Game.Render(Game.Cameras.Main, Game.Cameras.UI)
end
