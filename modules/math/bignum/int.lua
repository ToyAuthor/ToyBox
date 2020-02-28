
local tab = require "toy.table"
local bug = require "toy.debug"

local function init_integer_device()
	local maker = require("toy.math.bignum").new_int()

	local int_f = function(str)
		return maker:make(str)
	end

	return int_f
end

local int = init_integer_device()

local meta_of_int = {}

--[[
local function create_int_struct(str)
	local dev = int(str)

	local newone = getmetatable(dev)

	tab.fast_cover(newone,meta_of_int)

	return setmetatable(dev,newone)
end
--]]

local function create_int_struct(str)
	local dev

	if type(str)=="string" then
		dev = int(str)
	elseif type(str)=="number" then
		dev = int("0")
		dev:set_int(str)
	elseif type(str)=="table" then
		dev = int("0")
		dev:set(str)
	elseif type(str)=="nil" then
		dev = int("0")
	else
		bug.quit()
	end

	local newone = tab.fast_copy(meta_of_int)

	newone.__index = dev

	return setmetatable({},newone)
end

meta_of_int.__add = function(myself, rightvalue)
	local ans = create_int_struct()

	ans:set(myself)
	ans:add(rightvalue)

	return ans
end

meta_of_int.__sub = function(myself, rightvalue)
	local ans = create_int_struct()

	ans:set(myself)
	ans:sub(rightvalue)

	return ans
end

meta_of_int.__mul = function(myself, rightvalue)
	local ans = create_int_struct()

	ans:set(myself)
	ans:mul(rightvalue)

	return ans
end

meta_of_int.__div = function(myself, rightvalue)
	local ans = create_int_struct()

	ans:set(myself)
	ans:div(rightvalue)

	return ans
end

meta_of_int.__mod = function(myself, rightvalue)
	local ans = create_int_struct()

	ans:set(myself)
	ans:mod(rightvalue)

	return ans
end

meta_of_int.__eq = function(myself, rightvalue)
	return myself:eq(rightvalue)
end

meta_of_int.__lt = function(myself, rightvalue)
	return myself:lt(rightvalue)
end

meta_of_int.__le = function(myself, rightvalue)
	return myself:le(rightvalue)
end

meta_of_int.__unm = function(myself)
	local ans = create_int_struct()

	ans:set(myself)
	ans:unm()

	return ans
end

-- meta_of_int.__pow = ...

-- meta_of_int.__len = ...

meta_of_int.__concat = function(leftvalue, myself)
	return tostring(leftvalue) .. myself:str()
end

meta_of_int.__tostring = function(myself)
	return myself:str()
end

meta_of_int.__call = function(myself, arg)
	local ans = create_int_struct()
	local atype = type(arg)

	if arg==nil then
		return create_int_struct(myself)
	elseif atype=="number" then
		myself:set_int(arg)
	elseif atype=="string" then
		myself:set_str(arg)
	elseif atype=="table" then
		myself:set(arg)
	else
		bug.quit()
	end

	return create_int_struct(myself)
end

return
{
	new = create_int_struct,
}
