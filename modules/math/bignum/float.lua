
local tab = require "toy.table"
local bug = require "toy.debug"

local function init_float_device()
	local maker = require("toy.math.bignum").new_float()

	local float_f = function(str)
		return maker:make(str)
	end

	return float_f
end

local float = init_float_device()

local meta_of_float = {}

--[[
local function create_float_struct(str)
	local dev = float(str)

	local newone = getmetatable(dev)

	tab.fast_cover(newone,meta_of_float)

	return setmetatable(dev,newone)
end
--]]

local function create_float_struct(str)
	local dev

	if type(str)=="string" then
		dev = float(str)
	elseif type(str)=="number" then
		dev = float("0")
		dev:set_float(str)
	elseif type(str)=="table" then
		dev = float("0")
		dev:set(str)
	elseif type(str)=="nil" then
		dev = float("0")
	else
		bug.quit()
	end

	local newone = tab.fast_copy(meta_of_float)

	newone.__index = dev

	return setmetatable({},newone)
end

meta_of_float.__add = function(myself, rightvalue)
	local ans = create_float_struct()

	ans:set(myself)
	ans:add(rightvalue)

	return ans
end

meta_of_float.__sub = function(myself, rightvalue)
	local ans = create_float_struct()

	ans:set(myself)
	ans:sub(rightvalue)

	return ans
end

meta_of_float.__mul = function(myself, rightvalue)
	local ans = create_float_struct()

	ans:set(myself)
	ans:mul(rightvalue)

	return ans
end

meta_of_float.__div = function(myself, rightvalue)
	local ans = create_float_struct()

	ans:set(myself)
	ans:div(rightvalue)

	return ans
end

meta_of_float.__mod = function(myself, rightvalue)
	local ans = create_float_struct()

	ans:set(myself)
	ans:mod(rightvalue)

	return ans
end

meta_of_float.__eq = function(myself, rightvalue)
	return myself:eq(rightvalue)
end

meta_of_float.__lt = function(myself, rightvalue)
	return myself:lt(rightvalue)
end

meta_of_float.__le = function(myself, rightvalue)
	return myself:le(rightvalue)
end

meta_of_float.__unm = function(myself)
	local ans = create_float_struct()

	ans:set(myself)
	ans:unm()

	return ans
end

-- meta_of_float.__pow = ...

-- meta_of_float.__len = ...

meta_of_float.__concat = function(leftvalue, myself)
	return tostring(leftvalue) .. myself:str()
end

meta_of_float.__tostring = function(myself)
	return myself:str()
end

meta_of_float.__call = function(myself, arg)
	local ans = create_float_struct()
	local atype = type(arg)

	if arg==nil then
		return create_float_struct(myself)
	elseif atype=="number" then
		myself:set_float(arg)
	elseif atype=="string" then
		myself:set_str(arg)
	elseif atype=="table" then
		myself:set(arg)
	else
		bug.quit()
	end

	return create_float_struct(myself)
end

return
{
	new = create_float_struct,
}
