LinkConstraint = {}
LinkConstraint.__index = LinkConstraint

LinkConstraint.new = function(point1, point2, restingDistance, stiffness)
	local self = {}

	self.p1 = point1
	self.p2 = point2

	self.restingDistance = restingDistance or 50
	self.stiffness = stiffness or 0.005

	setmetatable(self, LinkConstraint)

	return self
end

function LinkConstraint:solve()
	local diffX = self.p1.pos.x - self.p2.pos.x
	local diffY = self.p1.pos.y - self.p2.pos.y
	local distance = math.sqrt(diffX * diffX + diffY * diffY)
	local difference = (self.restingDistance - distance) / distance

	local translateX = diffX * self.stiffness * difference
	local translateY = diffY * self.stiffness * difference

	local im1 = 1 / self.p1.mass;
    local im2 = 1 / self.p2.mass;
    local scalarP1 = (im1 / (im1 + im2)) * self.stiffness;
    local scalarP2 = self.stiffness - scalarP1;
    
    self.p1.pos.x = self.p1.pos.x + diffX * scalarP1 * difference;
    self.p1.pos.y = self.p1.pos.y + diffY * scalarP1 * difference;
    
    self.p2.pos.x = self.p2.pos.x - diffX * scalarP2 * difference;
    self.p2.pos.y = self.p2.pos.y - diffY * scalarP2 * difference;
end