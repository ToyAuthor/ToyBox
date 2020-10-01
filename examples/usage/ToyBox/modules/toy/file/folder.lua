
local  log = require "toy.logger"
local  dir = require "toy.file.folder"

local function view_files_in_folder(source,target)
	log.print("source position:" .. source)
	log.print("target position:" .. target)
end

dir.mapping_folder( "/tmp/folderA", "/tmp/folderB", view_files_in_folder)
