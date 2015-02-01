require("poep.lua")

Game = Game or {};

Game.myQuad = Game.myQuad or Quad.new()
Game.myQuad:setShader('shaders/effects.fx')
Game.myQuad:setPosition(-320, 0, 0)

RenderSettings.setFillMode('solid')
RenderSettings.setCullMode('back')

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

	local x, y, z = Game.myQuad:getPosition()
	Game.myQuad:setPosition(0, 0, 0)

	Camera.setPosition((math.sin(Game.t) * 100), (math.cos(Game.t) * 100), 0)
end

Game.Render = function () 
	
end