
local  opt = require "config"
local  env = require "toy.env"

local  run
local  print

if opt.support_print_utf8 then
	print = require("toy.logger").print
else
	print = _G.print
end

if env.os()=="windows" then
	run = function(item)
		os.execute(item)
	end
else
	run = function(item)
		os.execute("./" .. item)
	end
end

return
{
	run = run,
	print = print,
}
