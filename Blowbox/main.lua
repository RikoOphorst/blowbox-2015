require("poep.lua")

Game = Game or {};

Game.myQuad = Game.myQuad or Quad.new()
Game.myQuad:setShader('shaders/effects.fx')

Game.Init = function ()
	Content.loadTexture('tex1.png')
	Content.loadTexture('tex2.png')
	Content.loadShader('shaders/effects.fx')
	Content.loadShader('shaders/anotherFile.fx')
end

Game.Update = function (a)
	Game.t = (Game.t or 0) + a
	Game.myQuad:setAlpha(math.abs(math.sin(Game.t * 25)))

	Game.myQuad:setTexture("tex2.png")
	Game.myQuad:setRotation(0, 0, math.sin(Game.t))

	Game.myQuad:setPosition(math.sin(Game.t) * 100, 0, 0)

	Game.myQuad:setScale(math.abs(math.sin(Game.t)) + 1, 1, 1);

	print(Mouse.isDbl("L"))
end

Game.Render = function () 
	
end