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

	Game.player = Player.new(-50, -50)
end

Game.Update = function (dt)
	Game.dt = dt
	Game.elapsed = (Game.elapsed or 0) + dt

	--print("normal update")
end

Game.FixedUpdate = function(timesteps, step)
	Game.player:update(timesteps, step)
end

Game.Draw = function ()
	Game.Render(Game.Cameras.Main, Game.Cameras.UI)
end
