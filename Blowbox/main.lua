Game = Game or {};

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

	print("kjhsdksahgkdhkdsjs")
end

Game.Render = function ()
	
end

function balabla ()

	return unpack(sdakhbksd);

end