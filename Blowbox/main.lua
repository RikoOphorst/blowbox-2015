--require("poep.lua")

Game = Game or {};

Game.Init = function ()
	Game.myQuad = Quad.new()
end

Game.Update = function (a)
	Game.t = (Game.t or 0) + a
	Game.myQuad:setAlpha(math.abs(math.sin(Game.t * 5)))

	Game.myQuad:setShader("shaders/anotherFile.fx")
	Game.myQuad:setTexture("tex2.png")
	Game.myQuad:setRotation(0, 0, math.sin(Game.t))

	Game.myQuad:setPosition(math.sin(Game.t) * 100, 0, 0)
end

Game.Render = function () 
	
end