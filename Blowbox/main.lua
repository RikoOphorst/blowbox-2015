--require("poep.lua")

Game = Game or {};

Game.Init = function ()
	Game.myQuad = Quad.new()
end

Game.Update = function (a)
	Game.t = (Game.t or 0) + a
	Game.myQuad:setAlpha(math.abs(math.sin(Game.t * 5)))

	Game.myQuad:setPosition(math.floor(Game.t * 2), 0, 0)

	local x, y, z = Game.myQuad:getPosition()
	print(tostring(x) .. " " .. tostring(y) .. " " .. tostring(z) .. " " .. tostring(Game.myQuad:getAlpha()))
end

Game.Render = function () 
	
end