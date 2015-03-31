Vector2D = {}
Vector2D.__index = Vector2D

Vector2D.new = function (x, y)
    local self = setmetatable({ 
        x = x, 
        y = y
    }, Vector2D)

    return self
end

function Vector2D:isZero()
    return self.x == 0 and self.y == 0
end

function Vector2D:length()
    return math.sqrt(self:lengthSq())
end

function Vector2D:lengthSq()
    return self.x * self.x + self.y * self.y
end

function Vector2D:dot(other)
    return self.x * other.x + self.x * other.x
end

function Vector2D:cross(other)
    return self.x * other.y - self.y * other.x
end

function Vector2D:distance(other)
    return math.sqrt(self:distanceSq(other))
end

function Vector2D:distanceSq(other)
    return (other.x-self.x) * (other.x-self.x) + (other.y-self.y) * (other.y-self.y)
end

function Vector2D:equals(other)
    return self.x == other.x and self.y == other.y
end

function Vector2D:print()
    print("x: " .. self.x .. ", y: " .. self.y)
end

function Vector2D:perpCCW()
    return Vector2D.new(-self.y, self.x)
end

function Vector2D:perpCW()
    return Vector2D.new(self.y, -self.x)
end

function Vector2D:reverse()
    return Vector2D.new(-self.x, -self.y)
end

function Vector2D:add(other)
    return Vector2D.new(self.x + other.x, self.y + other.y)
end

function Vector2D:sub(other)
    return Vector2D.new(self.x - other.x, self.y - other.y)
end

function Vector2D:add(other)
    return Vector2D.new(self.x + other.x, self.y + other.y)
end

function Vector2D:mul(scalar)
    return Vector2D.new(self.x * scalar, self.y * scalar)
end

function Vector2D:div(scalar)
    return Vector2D.new(self.x / scalar, self.y / scalar)
end

function Vector2D:normalise()
    return self:div(self:length())
end

function Vector2D:scale(magnitude)
    return self:normalise():mul(magnitude)
end

function Vector2D:iperpCCW()
    local x, y = self.x, self.y

    self.x = -y
    self.y = x
end

function Vector2D:iperpCW()
    local x, y = self.x, self.y

    self.x = y
    self.y = -x
end

function Vector2D:ireverse()
    self.x = -self.x
    self.y = -self.y
end

function Vector2D:iadd(other)
    self.x = self.x + other.x
    self.y = self.y + other.y
end

function Vector2D:isub(other)
    self.x = self.x - other.x
    self.y = self.y - other.y
end

function Vector2D:imul(scalar)
    self.x = self.x * scalar
    self.y = self.y * scalar
end

function Vector2D:idiv(scalar)
    self.x = self.x / scalar
    self.y = self.y / scalar
end

function Vector2D:inormalise()
    self:idiv(self:length())
end

function Vector2D:iscale(magnitude)
    self:inormalise():imul(magnitude)
end