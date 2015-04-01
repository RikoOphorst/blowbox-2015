require('./scripts/utility/console.lua')

require('./scripts/physics/verlet.lua')

require('./scripts/ui/button.lua')
require('./scripts/ui/slider.lua')

function lerp(v0, v1, t)
	return (1-t)*v0 + t*v1
end

function random ()
	math.randomseed(os.time() * math.random())
	return math.random()
end

function randomRange(min, max)
	return random() * (max - min) + min
end

Game.Initialise = function ()
	Game.Cameras = {
		Main = Camera.new(),
		UI = Camera.new()
	}

	Game.Cameras.Main:setMode(CameraModes.Orthographic)
	Game.Cameras.UI:setMode(CameraModes.Orthographic)

	RenderSettings.setResolution(1024, 720)
	RenderSettings.setVSync(true)

	Game.RenderTargets = {
		Default = RenderTarget.new("default")
	}

	Game.RenderQueues = {
		Default = RenderQueue.new(Game.RenderTargets.Default)
	}

	ContentManager.loadTexture('./textures/background.png')
	ContentManager.loadTexture('./textures/highlighter.png')
	ContentManager.loadTexture('./textures/reset.png')
	ContentManager.loadTexture('./textures/reset_up.png')
	ContentManager.loadTexture('./textures/play.png')
	ContentManager.loadTexture('./textures/pause.png')
	ContentManager.loadTexture('./textures/switch.png')
	ContentManager.loadTexture('./textures/lenna.png')
	ContentManager.loadTexture('./textures/slider_bg.png')
	ContentManager.loadTexture('./textures/slider_title.png')
	ContentManager.loadTexture('./textures/slider_button.png')
	ContentManager.loadTexture('./textures/slider_title_none.png')
	ContentManager.loadTexture('./textures/slider_title_radius.png')
	ContentManager.loadTexture('./textures/slider_title_segments.png')
	ContentManager.loadTexture('./textures/slider_title_spoke.png')
	ContentManager.loadTexture('./textures/slider_title_tread.png')
	ContentManager.loadTexture('./textures/slider_title_size.png')
	ContentManager.loadTexture('./textures/slider_title_pinmod.png')
	ContentManager.loadTexture('./textures/slider_title_stiffness.png')
	ContentManager.loadShader('./shaders/blob.fx')
	ContentManager.loadShader('./shaders/cloth.fx')

	Game.Background = Quad.new(Game.RenderQueues.Default)
	Game.Background:setScale2D(1024, 720)
	Game.Background:setTexture('./textures/background.png')
	Game.Background:setPosition(0, 0, -1)

	Game.highlighter = Widget.new(Game.RenderQueues.Default)
	Game.highlighter:setAlpha(0)
	Game.highlighter:setScale2D(20, 20)
	Game.highlighter:setTexture('./textures/highlighter.png')
	Game.highlighter:setPosition(0, 0, 5)

	Game.resetBtn = Button.new(Game.RenderQueues.Default, 298, -337, 200, 75, './textures/reset.png')
	function Game.resetBtn:onHoverIn()
		Game.resetBtn.widget:setTexture('./textures/reset_up.png')
	end
	function Game.resetBtn:onDown()
		Game.resetBtn.widget:setTexture('./textures/reset_up.png')

		Game.CreatePhysics()
	end
	function Game.resetBtn:onHoverOut()
		Game.resetBtn.widget:setTexture('./textures/reset.png')
	end
	function Game.resetBtn:onUp()
		Game.resetBtn.widget:setTexture('./textures/reset.png')
	end

	Game.switchBtn = Button.new(Game.RenderQueues.Default, 298, -252, 200, 75, './textures/switch.png')
	function Game.switchBtn:onUp()
		if (Game.Mode == 'cloth') then
			Game.Mode = 'line'
		elseif (Game.Mode == 'line') then
			Game.Mode = 'blob'
		elseif (Game.Mode == 'blob') then
			Game.Mode = 'cloth'
		end

		Game.CreatePhysics()
	end

	Game.slider1 = Slider.new(Game.RenderQueues.Default, Vector2D.new(400, -90), 200, 75, './textures/slider_bg.png', './textures/slider_title_none.png', 200, 45, './textures/slider_button.png', 30, 75)
	Game.slider2 = Slider.new(Game.RenderQueues.Default, Vector2D.new(400, 20), 200, 75, './textures/slider_bg.png', './textures/slider_title_none.png', 200, 45, './textures/slider_button.png', 30, 75)
	Game.slider3 = Slider.new(Game.RenderQueues.Default, Vector2D.new(400, 130), 200, 75, './textures/slider_bg.png', './textures/slider_title_none.png', 200, 45, './textures/slider_button.png', 30, 75)
	Game.slider4 = Slider.new(Game.RenderQueues.Default, Vector2D.new(400, 240), 200, 75, './textures/slider_bg.png', './textures/slider_title_none.png', 200, 45, './textures/slider_button.png', 30, 75)

	Game.playpause = Widget.new(Game.RenderQueues.Default)
	Game.playpause:setAlpha(0)
	Game.playpause:setTexture('./textures/play.png')
	Game.playpause:setScale2D(150, 150)

	Game.Mode = "ragdoll"

	Game.CreatePhysics()
end

Game.Update = function (dt)
	Game.dt = dt
	Game.elapsed = (Game.elapsed or 0) + dt

	local mx, my = Mouse.getPosition()
	local mousePos = { x = mx - (1024/2), y = my - (720/2) }
	Game.resetBtn:update(mousePos)
	Game.switchBtn:update(mousePos)
	Game.slider1:update(mousePos)
	Game.slider2:update(mousePos)
	Game.slider3:update(mousePos)
	Game.slider4:update(mousePos)

	if (Game.Mode == 'blob') then
		for i, v in ipairs(Game.composite.particles) do
			local pos = Game.composite.particles[i].pos
			if (i - 1 ~= #Game.composite.particles - 1) then
				Game.polly:setPoint(pos.x, pos.y, 0, 0, 0.5, 0, 1, 0, 0, 0, 0, 0, i-1)
			else
				Game.polly:setPoint(pos.x, pos.y, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, i-1)
			end
		end
	elseif(Game.Mode == 'cloth') then
		local segments = Game.clothSegments

		for i, v in ipairs(Game.composite.particles) do
			local p1 = Game.composite.particles[i].pos
			local p2, p3

			if (math.fmod(i, segments) ~= 0) then
				if (i + segments < #Game.composite.particles) then
					p3 = Game.composite.particles[i+segments].pos
				else
					p3 = Game.composite.particles[i-segments].pos
				end

				p2 = Game.composite.particles[i+1].pos
			else
				if (i + segments < #Game.composite.particles) then
					p3 = Game.composite.particles[i+segments].pos
				else
					p3 = Game.composite.particles[i-segments].pos
				end

				p2 = Game.composite.particles[i-1].pos
			end

			local distX = p1:distance(p2)
			local distY = p1:distance(p3)

			local vX = distX / (Game.clothDefaultWidth * 0.8) - 1
			local vY = distY / (Game.clothDefaultHeight * 0.8) - 1

			local u, v

			u = (i % segments) / segments
			v = (i / segments) / segments

			if (i%segments == 0) then u = 1 end
			if (v > 1) then v = 1 end

			Game.polly:setPoint(p1.x, p1.y, 0, 0, 0.5, 0, 1, vX, vY, 1, u, v, i-1)
		end
	elseif (Game.Mode == 'line') then
		for i=0, (#Game.composite.particles-1) * 2, 2 do
			local pos = Game.composite.particles[(i / 2) + 1].pos
			Game.polly:setPoint(pos.x, pos.y - 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, i)
			Game.polly:setPoint(pos.x, pos.y + 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, i+1)
		end
	elseif (Game.Mode == 'ragdoll') then
		for i, v in ipairs(Game.ragdolls) do
			Game.ragdolls[i]:update()
		end
	end

	if (Keyboard.isPressed("Space")) then
		Game.simulate = not Game.simulate

		Game.playpause:setAlpha(1)

		if (Game.simulate) then
			Game.playpause:setTexture('./textures/play.png')
		else
			Game.playpause:setTexture('./textures/pause.png')
		end
	end

	if (Game.playpause:getAlpha() > 0) then
		Game.playpause:setAlpha(Game.playpause:getAlpha() - 0.04)
	end

	local speed = 0.5


	if (Game.simulate) then
		if (Keyboard.isDown("W")) then
			for j, w in ipairs(Game.Physics.composites) do
				for i, v in ipairs(Game.Physics.composites[j].particles) do
					Game.Physics.composites[j].particles[i].pos.y = Game.Physics.composites[j].particles[i].pos.y - speed * randomRange(0, 2)
				end
			end
		end

		if (Keyboard.isDown("A")) then
			for j, w in ipairs(Game.Physics.composites) do
				for i, v in ipairs(Game.Physics.composites[j].particles) do
					Game.Physics.composites[j].particles[i].pos.x = Game.Physics.composites[j].particles[i].pos.x - speed * randomRange(0, 2)
				end
			end
		end

		if (Keyboard.isDown("S")) then
			for j, w in ipairs(Game.Physics.composites) do
				for i, v in ipairs(Game.Physics.composites[j].particles) do
					Game.Physics.composites[j].particles[i].pos.y = Game.Physics.composites[j].particles[i].pos.y + speed * randomRange(0, 2)
				end
			end
		end

		if (Keyboard.isDown("D")) then
			for j, w in ipairs(Game.Physics.composites) do
				for i, v in ipairs(Game.Physics.composites[j].particles) do
					Game.Physics.composites[j].particles[i].pos.x = Game.Physics.composites[j].particles[i].pos.x + speed * randomRange(0, 2)
				end
			end
		end
	end

	local particle = Game.Physics:getNearestParticle(mousePos)

	if (particle ~= nil) then
		Game.highlighter:setAlpha(1)
		Game.highlighter:setPosition(particle.pos.x, particle.pos.y, 5)

		if (Mouse.isDown("left")) then
			Game.selectedParticle = particle
		end
	else
		Game.highlighter:setAlpha(0)
	end

	if (Game.selectedParticle ~= nil) then
		if (not Mouse.isDown("left")) then
			Game.selectedParticle = nil
		else
			Game.selectedParticle.pos.x = mousePos.x
			Game.selectedParticle.pos.y = mousePos.y
		end
	end
end

Game.FixedUpdate = function(timesteps, step)
	if (Game.simulate) then
		Game.Physics:update(step)
	end
end

Game.Draw = function ()
	Game.Render(Game.Cameras.Main, Game.Cameras.UI)
end

Game.OnReload = function (path)
	--Game.CreatePhysics()
end

Game.CreatePhysics = function ()
	Game.simulate = true
	Game.playpause:setTexture('./textures/pause.png')
	Game.playpause:setAlpha(1)

	Game.Physics = Verlet.new()

	if (Game.Mode == "blob") then
		Game.slider1:setTitle('./textures/slider_title_segments.png', 200, 45)
		Game.slider2:setTitle('./textures/slider_title_radius.png', 200, 45)
		Game.slider3:setTitle('./textures/slider_title_spoke.png', 200, 45)
		Game.slider4:setTitle('./textures/slider_title_tread.png', 200, 45)

		local segments = math.floor(40 * Game.slider1:getValue() + 0.5)
		local radius = 100 * Game.slider2:getValue()
		local spokestiffness = 0.1 * Game.slider3:getValue() 
		local treadstiffness = 0.7 * Game.slider4:getValue()

		Game.composite = Game.Physics:addBlob(Vector2D.new(-89, -100), radius, segments, spokestiffness, treadstiffness)

		local vertices = {}
		local indices = {}

		for i, v in ipairs(Game.composite.particles) do
			local vert = {
				Game.composite.particles[i].pos.x,
				Game.composite.particles[i].pos.y,
				0
			}

			table.insert(vertices, vert)
		end

		for i=0, segments, 1 do
			local idx = i + 1
			if (i == segments) then
				table.insert(indices, segments - 1)
				table.insert(indices, 0)
				table.insert(indices, segments)
			else
				table.insert(indices, idx)
				table.insert(indices, i)
				table.insert(indices, #Game.composite.particles - 1)
			end
		end

		Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
		Game.polly:setShader('./shaders/blob.fx')
		Game.ragdolls = {}
	end

	if (Game.Mode == "cloth") then
		Game.slider1:setTitle('./textures/slider_title_segments.png', 200, 45)
		Game.slider2:setTitle('./textures/slider_title_size.png', 200, 45)
		Game.slider3:setTitle('./textures/slider_title_pinmod.png', 200, 45)
		Game.slider4:setTitle('./textures/slider_title_stiffness.png', 200, 45)

		local origin = Vector2D.new(-89, -100)
		local width = 300 * Game.slider2:getValue()
		local height = 200 * Game.slider2:getValue()
		local segments = math.floor(10 * Game.slider1:getValue() + 0.5)
		local pinMod = math.floor(4 * Game.slider3:getValue() + 0.5)
		local stiffness = 0.1 * Game.slider4:getValue()

		Game.clothSegments = segments
		Game.clothDefaultWidth = width / segments
		Game.clothDefaultHeight = height / segments

		Game.composite = Game.Physics:addCloth(origin, width, height, segments, pinMod, stiffness)

		local vertices = {}
		local indices = {}

		for i, v in ipairs(Game.composite.particles) do
			local vert = {
				Game.composite.particles[i].pos.x,
				Game.composite.particles[i].pos.y,
				0
			}

			table.insert(vertices, vert)
		end

		for y=0, segments - 1, 1 do
			for x=0, segments - 2, 1 do
				table.insert(indices, y*segments+x)
				table.insert(indices, (y+1)*segments+x)
				table.insert(indices, (y+1)*segments+x+1)
				table.insert(indices, (y+1)*segments+x+1)
				table.insert(indices, y*segments+x+1)
				table.insert(indices, y*segments+x)
			end
		end

		Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
		Game.polly:setShader('./shaders/cloth.fx')
		Game.polly:setTexture('./textures/lenna.png')
		Game.ragdolls = {}
	end

	if (Game.Mode == "line") then
		local verts = {}

		local startingpoint = Vector2D.new(-440, 0)
		local endpoint = Vector2D.new(255, 0)
		local segments = 50
		local pinMod = 20

		for i = 1, segments, 1 do
			local vert = Vector2D.new(
					lerp(
						startingpoint.x, 
						endpoint.x, 
						i/segments
					),
					lerp(
						startingpoint.y,
						endpoint.y,
						i/segments
					)
				)

			table.insert(verts, vert)
		end

		Game.composite = Game.Physics:addLine(verts, 0.1)

		for i=1, segments, 1 do
			if (math.fmod(i, pinMod) == 0 or i == 1 or i == segments) then
				Game.composite:pin(i)
			end
		end

		local vertices = {}
		local indices = {}

		for i, v in ipairs(Game.composite.particles) do
			local particle = Game.composite.particles[i]
			table.insert(vertices, {
				particle.pos.x,
				particle.pos.y - 5,
				0
			})

			table.insert(vertices, {
				particle.pos.x,
				particle.pos.y + 5,
				0
			})
		end

		for i=1, #vertices, 2 do
			table.insert(indices, i-1)
			table.insert(indices, i+2)
			table.insert(indices, i)
			table.insert(indices, i-1)
			table.insert(indices, i+2)
			table.insert(indices, i+1)
		end

		Game.polly = Polygon.new(Game.RenderQueues.Default, vertices, indices, Topology.TriangleList)
		Game.ragdolls = {}
	end

	if (Game.Mode == 'ragdoll') then
		Game.simulate = false

		Game.polly = nil

		Game.ragdolls = {}

		for i=1, 200, 1 do
			math.randomseed(i * os.time())

			local ragdoll = Ragdoll.new(Game.RenderQueues.Default, Vector2D.new(math.random() * 600 - 400, math.random() * 200 - 300), randomRange(30, 60))

			table.insert(Game.ragdolls, ragdoll)

			table.insert(Game.Physics.composites, ragdoll.composite)
		end
	end
end