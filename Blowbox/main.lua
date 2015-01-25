--require("poep.lua")

Game = {};

local q = q or Quad:new()
local t = t or 0

Game.Init = function () 
	
end


Game.dts = Game.dts or {}

Game.Update = function (a)
	t = t + a 
	q:SetAlpha(math.abs(math.sin(t*5)))
end

Game.Render = function () 
	--print("Rendur")
end