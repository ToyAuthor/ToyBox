
local  opt = require "config"
local  env = require "toy.env"

local  Run
local  Print

if opt.support_print_UTF8 then
	Print = require("toy.logger").print
else
	Print = print
end

if env.os()=="windows" then
	Run = function(item)
		os.execute(item)
	end
else
	Run = function(item)
		os.execute("./" .. item)
	end
end

return
{
	run = Run,
	print = Print,
}
