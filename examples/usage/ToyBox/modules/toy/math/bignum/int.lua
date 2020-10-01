
local bug = require "toy.debug"
local log = require "toy.logger"
local int = require("toy.math.bignum.int").new

local function main()
	local  a = int("126")
	local  b = int("124")
	local  c = a+b
	local  d = int()    -- Default value is zero

--	log.print("look a:" .. a:str() )
	log.print("look a:" .. a )
	log.print("look b:" .. b )
	log.print("look c:" .. c )
	log.print("look d:" .. d )

	if a>b then
		log.print("a>b")
	else
		log.print("a<=b")
	end

--	local  clone = b                      ----------(X)  Not a deep copy
--	local  clone = -b                     ----------(O)
--	local  clone = b()                    ----------(O)
--	local  clone = int(b)                 ----------(O)

--	local  clone = 100                    ----------(X)
--	local  clone = int(100)               ----------(O)
--	local  clone = int("100")             ----------(O)

--	local  clone = int(); clone = b       ----------(X)  Not a deep copy
--	local  clone = int(); clone = b()     ----------(O)  Apply new memory to store value
--	local  clone = int(); clone = int(b)  ----------(O)  Apply new memory to store value
--	local  clone = int(); clone(b)        ----------(O)  Use same memory to store value
--	local  clone = int(); clone = 100     ----------(X)
--	local  clone = int(); clone(100)      ----------(O)
--	local  clone = int(); clone("100")    ----------(O)
end

if bug.catch(main) then
	bug.warn("Something wrong")
end
