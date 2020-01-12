
local  MARCO = _G._TOY_SYSTEM_MESSAGE
local  oops = require("toy.debug").oops

if MARCO == nil then
	oops()
else
	if MARCO.project_path == nil then
		oops()
	end
end

local function run_project(module_name,project_path,resource_path)
	local  project_path_origin  = MARCO.project_path
	local  resource_path_origin = MARCO.resource_path

	MARCO.project_path  = project_path
	MARCO.resource_path = resource_path

	require(module_name)

	MARCO.project_path  = project_path_origin
	MARCO.resource_path = resource_path_origin
end

return
{
	get_project_path = function() return MARCO.project_path end,
	get_resource_path = function()
		if MARCO.resource_path==nil then
			oops()
		end
		return MARCO.resource_path
	end,
	_run_project = run_project,
}
