
local png  = require "toy.file.export.png"
local bug  = require "toy.debug"
local file = require "toy.file"

local function load_image_file(folder,filename)
	local  stream = file.create_stream("default")   -- Create a file stream using <cstdio>.
	local  buffer = file.create_image_buffer()      -- Create a buffer for loading image data.

	stream:open_dir(folder)
	stream:open(filename)
	stream:load_image(buffer)

	return buffer
end

local function main()
	image = load_image_file("D:/photos","002.jpg")
	png.export("D:/photos/003.png",image)
end

if bug.catch(main)==false then
	bug.oops()
end
