
local  rex = require "toy.regex"
local  oops = require("toy.debug").oops

-- "image.jpg" -> "jpg"
-- "/opt/map/image.jpg" -> "jpg"
-- "/opt/map/image.jpg.png" -> "png"
-- "/opt/map/image.jpg%d" -> "nil"
-- "/opt/map/image.jpgd" -> "jpgd"
-- "/opt/map/imagejpg" -> nil
-- "/opt/map/" -> nil
local function get_extension(str)

	local times = 0
	local ans

	local function view_result(var)
		times = times+1

		if times==1 then
			ans = var
		end
	end

	if not rex.search([[(?<=[^/][\.])\w*$]],str,view_result) then
		ans = nil
	end

	return ans
end

-- "image.jpg" -> "image"
-- "/opt/map/image.jpg" -> "image"
-- "/opt/map/image.jpg.png" -> "image.jpg"
-- "/opt/map/image.jpg%d" -> "image.jpg%d"
-- "/opt/map/image.jpgd" -> "image"
-- "/opt/map/imagejpg" -> "imagejpg"
-- "/opt/map/" -> nil
local function get_filename(str)

	local times = 0
	local ans

	local function view_result(var)
		times = times+1

		if times==1 then
			ans = var
		end
	end

	if not rex.search([=[[^/]+?(?=\.\w*$|$)]=],str,view_result) then
		ans = nil
	end

	return ans
end

return
{
	get_extension = get_extension,
	get_filename = get_filename,
}
