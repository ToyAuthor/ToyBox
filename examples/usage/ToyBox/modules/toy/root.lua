
local sys = require "toy.root"       -- Only support player.exe
local log = require "toy.logger"

log.print("The project's location:" .. sys.get_project_path())

local resource_folder = sys.get_resource_path()

if resource_folder then
	log.print("The resource folder:" .. resource_folder)
else
	log.print("There is no resource")
end
