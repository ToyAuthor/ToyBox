
local  msg = require "toy.logger"
local  dir = require "toy.file.folder"

local function view_files_in_folder(source,target)
	msg.print("source position:" .. source)
	msg.print("target position:" .. target)
end

dir.mapping_folder( "/tmp/folderA", "/tmp/folderB", view_files_in_folder)
