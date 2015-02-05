require("poep.lua")

Game = Game or {};

RenderSettings.setFillMode('solid')
RenderSettings.setCullMode('none')

Game.myWidget = Game.myWidget or Widget.new()
Game.myWidget:setPosition(0, 100, 0)

RenderSettings.setFullscreen(0)
RenderSettings.setVsync(1)

Game.myWidget:setTexture("tex1.png")

Game.Init = function ()
	Content.loadTexture('tex1.png')
	Content.loadTexture('tex2.png')
	Content.loadShader('shaders/effects.fx')
	Content.loadShader('shaders/anotherFile.fx')
end

Game.Update = function (a)
	Game.t = (Game.t or 0) + a

	--Game.myQuad:setPosition(x+1, 0, 0)

	Camera.setPosition((math.sin(Game.t) * 100), (math.cos(Game.t) * 100), 0)

	--Line.draw(-200, 0, 0, 1, 1, 1, 100, 200, 0, 0, 0, 0)
end

Game.Render = function () 
	
end