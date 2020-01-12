
local sys = require "toy.root"       -- Only support player.exe
local msg = require "toy.logger"

msg.print("The project's location:" .. sys.get_project_path())

local resource_folder = sys.get_resource_path()

if resource_folder then
	msg.print("The resource folder:" .. resource_folder)
else
	msg.print("There is no resource")
end
