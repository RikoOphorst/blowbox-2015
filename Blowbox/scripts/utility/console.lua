
-- Hacky solution to the tostring problem we are having in normal prints, should actually be engine sided but don't have any time to implement this right now
if (printCache == nil) then
	printCache = print
	print = function (string)
		printCache(tostring(string))
	end
end