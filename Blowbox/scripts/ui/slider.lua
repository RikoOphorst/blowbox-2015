Slider = {}
Slider.__index = Slider

Slider.new = function (queue, origin, width, height, background, title, twidth, theight, button, bwidth, bheight)
	local self = {}

	self.background = Widget.new(queue)
	self.background:setTexture(background)
	self.background:setScale2D(width, height)
	self.background:setPosition2D(origin.x, origin.y)

	self.title = Widget.new(queue)
	self.title:setTexture(title)
	self.title:setScale2D(twidth, theight)
	self.title:setPosition2D(origin.x, origin.y - 53)

	self.button = Widget.new(queue)
	self.button:setTexture(button)
	self.button:setScale2D(bwidth, bheight)
	self.button:setPosition2D(origin.x, origin.y)

	self.pos = Vector2D.new(origin.x, origin.y)
	self.hovered = false
	self.clicked = false
	self.size = Vector2D.new(bwidth, bheight)
	self.width = width
	self.height = height
	self.origin = origin

	setmetatable(self, Slider)

	return self
end

function Slider:setTitle(title, width, height)
	self.title:setTexture(title)
	self.title:setScale2D(width, height)
	self.pos.x = self.origin.x
	self.pos.y = self.origin.y
end

function Slider:getValue()
	return (self.pos.x - self.origin.x + self.width / 2) / self.width * 2
end

function Slider:update(mousePos)
	if (mousePos.x > self.origin.x - self.width / 2 and
		mousePos.x < self.origin.x + self.width / 2 and
		mousePos.y > self.origin.y - self.height / 2 and
		mousePos.y < self.origin.y + self.height / 2) then
		if (not self.hovered) then
			self.hovered = true
			self:onHoverIn()
		end
	else
		if (self.clicked) then
			self.clicked = false
			self:onUp()
		end

		if (self.hovered) then
			self.hovered = false
			self:onHoverOut()
		end
	end

	if (self.hovered) then
		if (Mouse.isDown('left')) then
			if (not self.clicked) then
				self.clicked = true
				self:onDown()
			end

			self.pos.x = mousePos.x
		else
			if (self.clicked) then
				self.clicked = false
				self:onUp()
			end
		end
	end

	if (self.pos.x > self.origin.x + self.width / 2) then
		self.pos.x = self.origin.x + self.width / 2
	end

	if (self.pos.x < self.origin.x - self.width / 2) then
		self.pos.x = self.origin.x - self.width / 2
	end

	self.button:setPosition(self.pos.x, self.pos.y, 5)
	self.button:setScale(self.size.x, self.size.y, 1)
end

function Slider:onHoverIn()

end

function Slider:onHoverOut()

end

function Slider:onDown()

end

function Slider:onUp()

end