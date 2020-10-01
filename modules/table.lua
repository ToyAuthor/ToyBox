
-- Transform array<string> into map<string,number>. Return table will look like C/C++ enum.
--[[
local Origin_ID = {
	"NUM_A",
	"NUM_B",
	"NUM_C",
	"NUM_D"
}
local ID = table.enum(Origin_ID)
]]
local function make_enum( source_table, init_value )
	local result={}
	local begin = 0

	if init_value then
		begin = init_value
	end

	for key, value in ipairs(source_table) do
		result[value] = key + begin - 1
	end

	return result
end

--[[
local function fast_clone(t)
	return {unpack(t)}
end]]

local function fast_clone(t)
	local result = {}

	for key, value in pairs(t) do
		result[key] = value
	end

	return result
end

-- Fast than deep_clone
local function clone(t)
	return setmetatable(fast_clone(t), getmetatable(t))
end

-- Clone everything.
local function deep_clone(t)
	local mt = getmetatable(t)
	local result = {}

	for key, value in pairs(t) do
		if type(value) == "table" then
			result[key] = deep_clone(value)
		else
			result[key] = value
		end
	end

	setmetatable(result, mt)

	return result
end

local function fast_cover_table(t1,t2)
	for key, value in pairs(t2) do
		t1[key] = value
	end
end

-- t1 = t1 + t2
local function cover_table(t1,t2)
	for key, value in pairs(t2) do
		t1[key] = value
	end

	setmetatable(t1, getmetatable(t2))
end

-- return t1 + t2
local function merge_table(t1,t2)
	local t = {}
	cover_table(t,t1)
	cover_table(t,t2)
	return t
end

-- Delete every each element of the given table.
local function empty_table(t)
	for k in pairs(t) do
		t[k]=nil
	end

	setmetatable(t, nil)
end

-- t1 = t2
local function move_table(t1,t2)
	empty_table(t1)
	cover_table(t1,t2)
end

--[[
	Call make_series(x,y,z) will return this table:
	t =
	{
		[x  ] = z + x ,
		[x+1] = z + x + 1,
		[x+2] = z + x + 2,
		[x+3] = z + x + 3,
		...
		[y  ] = z + y
	}
]]
local function make_series(start,ending,offset)
	local t={}

	for i=start,ending do
		t[i]=i+offset
	end

	return t
end

--local default_pointer = _G.print                     -- Native Lua output device.
  local default_pointer = require("toy.logger").print  -- It support UTF-8 encoding.
local function print_table(ttt,my_printer)
	my_printer = my_printer or default_pointer

	local indent_dev =
	{
		str = function (self)
			return string.rep(self._text,self._size)
		end,

		move = function (self,offset)
			self._size = self._size + offset
		end,

		_size = 0,
		_text = "    "     -- One Tab
	}

	local function modify_key(key)
		if type(key)=="string" then
			key = [["]] .. key .. [["]]
		elseif type(key)=="boolean" then
			if key then
				key = "true"
			else
				key = "false"
			end
		end

		return key
	end

	local function print_my_table(tt,indent)
		my_printer(indent:str() .. "{")
		indent:move(1)

		for key, value in pairs(tt) do
			key = modify_key(key)

			if type(value)=="table" then
				my_printer(indent:str() .. key .. " =")
				print_my_table(value,indent)
			elseif type(value)=="string" then
				my_printer(indent:str() .. key .. [[ = "]] .. value .. [["]])
			elseif type(value)=="boolean" then
				if value then
					my_printer(indent:str() .. key .. " = " .. "true")
				else
					my_printer(indent:str() .. key .. " = " .. "false")
				end
--			elseif type(value)=="userdata" then     No, no such option. Too bad.
			else
				my_printer(indent:str() .. key .. " = " .. value)
			end
		end

		indent:move(-1)
		my_printer(indent:str() .. "}")
	end

	print_my_table(ttt,indent_dev)
end

return
{
	enum = make_enum,
	move = move_table,
	fast_cover = fast_cover_table,
	cover = cover_table,
	merge = merge_table,
	clean = empty_table,
	print = print_table,
	fast_copy = fast_clone,
	copy = clone,
	deep_copy = deep_clone,
	series = make_series,
	--[[
	is_empty = function(t)
		return next(t)==nil
	end,
	]]
}
