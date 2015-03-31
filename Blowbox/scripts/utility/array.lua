Array = {}
Array.__index = Array

Array.new = function (array)
	local self = {}

	self.table = array or {}
	self.size = 0

	setmetatable(self, Array)

	self:calculateSize()

	return self
end

function Array:calculateSize()
	local size = 1

print ("yoo")
	for i, v in ipairs(self.table) do
		print ("yo")
		size = size + 1
	end

	self.size = size

	return size
end

function Array:at(i)
	return self.table[i]
end

function Array:push(element)
	self.size = self.size + 1

	self.table[self.size] = element

	return self.size
end

function Array:pop()
	self.size = self.size - 1

	self.table[self.size] = nil
end

function Array:replace(idx, element)
	self.table[idx] = element
end

function Array:iterate(func)
	print("iteration")
	for i, v in ipairs(self.table) do
		func(i, v)
	end
end