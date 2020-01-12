
local  msg = require "toy.logger"
local  cpp = require "toy.cpp"

return
{
	warn = function(str)
		msg.print("Warning:" .. str)
		msg.print("Warning:" .. debug.getinfo(2,'S').source .. ":" .. debug.getinfo(2,'l').currentline )
	end,

	oops = function()
		msg.print("Warning:" .. debug.getinfo(2,'S').source .. ":" .. debug.getinfo(2,'l').currentline )
	end,

	stop = function(str)
		msg.print("Error:" .. str)
		msg.print("Error:" .. debug.getinfo(2,'S').source .. ":" .. debug.getinfo(2,'l').currentline )
		error()
	end,

	quit = function(...)
		local first_arg = select(1,...)

		if type(first_arg)=="string" then
			msg.print("Error:" .. first_arg)
		end

		msg.print("Error:" .. debug.getinfo(2,'S').source .. ":" .. debug.getinfo(2,'l').currentline )
		error()
	end,

	-- Prototype:bool(function)
	-- Parameters:
	--     1:a closure
	--         Prototype:void(void)
	--         Parameters:none
	--         Return Values:none
	-- Return Values:return true if something wrong.
	catch = function(func)
		local result = false

		-- Try to catch "std::exception" from C++ side.
		local function foo()
			result = cpp.catch(func)
		end

		local status, err, ret = xpcall(foo,debug.traceback)

		if status==false then
			result = true

			msg.print(err)

			if type(ret)=="string" then
				msg.print(ret)
			end
		end

		return result
	end,
}
