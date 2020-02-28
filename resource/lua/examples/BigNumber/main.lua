
local bug = require "toy.debug"
local msg = require "toy.logger"
local int = require("toy.math.bignum.int").new
local float = require("toy.math.bignum.float").new

local function main()
	local  a = int("126")
	local  b = int("124")
	local  c = a+b
	local  d = int()    -- Default value is zero

--	msg.print("look a:" .. a:str() )
	msg.print("look a:" .. a )
	msg.print("look b:" .. b )
	msg.print("look c:" .. c )
	msg.print("look d:" .. d )

	if a~=b then
		msg.print("a>b")
	else
		msg.print("a<=b")
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

local function main2()
	local  a = float("222222.5")
	local  b = float("333333.5")
	local  c = a+b
	local  d = float()    -- Default value is zero

--	msg.print("look a:" .. a:str() )
	msg.print("look a:" .. a )
	msg.print("look b:" .. b )
	msg.print("look c:" .. c )
	msg.print("look d:" .. d )

	if a~=b then
		msg.print("a>b")
	else
		msg.print("a<=b")
	end

end

if bug.catch(main2) then
	bug.warn("Something wrong")
end
