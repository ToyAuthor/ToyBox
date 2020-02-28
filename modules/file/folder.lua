
local   bfs = require "toy.path"
--local   aux = require "toy.file.check"
local   quit = require("toy.debug").quit
local   mapping_folder = require "toy.file._mappingfolder"
local   visit_folder = require "toy.file._visitfolder"

return
{
	-- Prototype:void(string,string,function)
	-- Parameters:
	--     1:the name of source folder
	--     2:the name of target folder
	--     3:a closure
	--         Prototype:void(string,string)
	--         Parameters:
	--             1:source file name
	--             2:target file name
	--         Return Values:none
	-- Return Values:none
	mapping_folder = function(source_folder,target_folder,func)
	--	aux.force_empty_folder(target_folder)
		if bfs.is_folder_has_child(source_folder) then
			mapping_folder(source_folder,target_folder,func)
		else
			quit()
		end
	end,

	visit_folder = function( folder, func )
		visit_folder( folder, func )
	end,
}
