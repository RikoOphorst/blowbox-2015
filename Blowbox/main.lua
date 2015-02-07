require("poep.lua")

Game = Game or {};

RenderSettings.setFillMode('solid')
RenderSettings.setCullMode('none')

Game.w1 = Game.w1 or Widget.new()
Game.w1:setPosition(0, 50, 0)
Game.w1:setRotation(0, 0, 3)
Game.w1:setTexture("tex1.png")

Game.w2 = Game.w2 or Widget.new(Game.w1)
Game.w2:setPosition(50, 0, 0)
Game.w2:setTexture("tex2.png")

Game.w3 = Game.w3 or Widget.new(Game.w2)
Game.w3:setPosition(50, 0, 0)
Game.w3:setTexture("tex2.png")

Game.w4 = Game.w4 or Widget.new(Game.w3)
Game.w4:setPosition(50, 10, 0)
Game.w4:setRotation(0, 0, 3)
Game.w4:setTexture("tex2.png")

RenderSettings.setFullscreen(0)
RenderSettings.setVsync(1)

Game.Init = function ()
	Content.loadTexture('tex1.png')
	Content.loadTexture('tex2.png')
	Content.loadShader('shaders/effects.fx')
	Content.loadShader('shaders/anotherFile.fx')
end

Game.Update = function (a)
	Game.t = (Game.t or 0) + a

	--Game.myQuad:setPosition(x+1, 0, 0)

	Game.w2:setAlpha(math.sin(Game.t * 10))

	--Line.draw(-200, 0, 0, 1, 1, 1, 100, 200, 0, 0, 0, 0)
end

Game.Render = function () 
	
end