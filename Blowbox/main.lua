require("./scripts/utility/class.lua")
require("./scripts/math/vector.lua")
require("./scripts/player.lua")

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

	Game.player = Player(Game.RenderQueues.Default)
end

Game.Update = function (dt)
	Game.t = (Game.t or 0) + 1
	
	Game.player:setScale2D(100, 100)
end

Game.Draw = function ()
	Game.Render(Game.Cameras.Main, Game.Cameras.UI)
end
