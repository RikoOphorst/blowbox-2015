Button = {}
Button.__index = Button

Button.new = function (queue, x, y, width, height, texture)
	local self = {}

	self.widget = Widget.new(queue)
	self.widget:setPosition2D(x, y)
	self.widget:setScale2D(width, height)
	self.widget:setTexture(texture)
	self.widget:setOffset2D(0.5, 0.5)

	self.pos = Vector2D.new(x, y)
	self.size = Vector2D.new(width, height)

	self.hovered = false
	self.clicked = false

	setmetatable(self, Button)

	return self
end

function Button:update(mousePos)
	if (mousePos.x > self.pos.x and
		mousePos.x < self.pos.x + self.size.x and
		mousePos.y > self.pos.y and
		mousePos.y < self.pos.y + self.size.y) then

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
		else
			if (self.clicked) then
				self.clicked = false
				self:onUp()
			end
		end
	end

	self.widget:setPosition(self.pos.x, self.pos.y, self.widget:getZ())
	self.widget:setScale(self.size.x, self.size.y, 1)

end

function Button:onHoverIn()

end

function Button:onHoverOut()

end

function Button:onDown()

end

function Button:onUp()

end