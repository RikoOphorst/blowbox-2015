VerletPoint = {}
VerletPoint.__index = VerletPoint

VerletPoint.new = function (x, y)
	local self = {}

	self.pos = Vector2D.new(x, y)
	self.lastpos = Vector2D.new(x, y)

	self.vel = Vector2D.new(0, 0.2)
	self.acc = Vector2D.new(0, 0.2)

	setmetatable(self, VerletPoint)

	return self
end

function VerletPoint:update()
	self.vel = self.pos:sub(self.lastpos)

	self.lastpos = Vector2D.new(self.pos.x, self.pos.y)

	self.pos = self.pos:add(self.vel):add(self.acc)
end

LinkConstraint = {}
LinkConstraint.__index = LinkConstraint

LinkConstraint.new = function(point1, point2, restingDistance)
	local self = {}

	self.p1 = point1
	self.p2 = point2

	self.restingDistance = restingDistance

	setmetatable(self, LinkConstraint)

	return self
end

function LinkConstraint:solve()
	local diffX = self.p1.pos.x - self.p2.pos.x
	local diffY = self.p1.pos.y - self.p2.pos.y
	local distance = math.sqrt(diffX * diffX + diffY * diffY)
	local difference = (self.restingDistance - distance) / distance

	local translateX = diffX * 0.005 * difference
	local translateY = diffY * 0.005 * difference

	self.p1.pos.x = self.p1.pos.x + translateX
	self.p1.pos.y = self.p1.pos.y + translateY

	self.p2.pos.x = self.p2.pos.x - translateX
	self.p2.pos.y = self.p2.pos.y - translateY
end