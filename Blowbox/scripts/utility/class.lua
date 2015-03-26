function class(parent, constructor)
	local table = {}

	table.new = function(...)
		local self = parent.new(...)

		local mt = getmetatable(self)

		mt.__index = function(t, field)
			if (rawget(table, field) ~= nil) then
				return rawget(table, field)
			else
				return getmetatable(parent)[field]
			end
		end

		setmetatable(getmetatable(self), mt)

		constructor(self, ...)

		return self
	end

	setmetatable(table, {
		__index = table,
		__call = function(t, ...)
			return table.new(...)
		end
	})

	return table
end