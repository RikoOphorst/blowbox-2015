Game = {};

Game.Init = function () 
	print("Initur")
end


Game.dts = Game.dts or {}

Game.Update = function (a) 
	table.insert(Game.dts, a)
	local sum = 0
	if (#Game.dts > 100) then
		table.remove(Game.dts, 1)
	end

	for k,v in ipairs(Game.dts) do
		sum = sum + v
	end

	local fps = math.floor(1 / (sum / #Game.dts) + 0.5)

	print("FPS: " .. tostring(fps) .. "/60")
end

Game.Render = function () 
	print("Rendur")
end