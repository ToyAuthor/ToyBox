
local bug  = require "toy.debug"
local fs   = require "toy.file"
local webp = require "toy.file.loader.webp"
--local png  = require "toy.file.loader.png"

local function load_image_file(folder,filename)
--	local  stream = fs.create_stream("zip")       -- Create a file stream with zlib.
--	local  stream = fs.create_stream("7zip")      -- Create a file stream with 7zip.
	local  stream = fs.create_stream("default")   -- Create a file stream with folder.

	local  buffer = fs.create_image_buffer()      -- Create a empty buffer for loading image data.

	stream:open_dir(folder)         -- Open a directory/archive for searching files.
	stream:open(filename)           -- Open file stream.
	webp.load_image(stream,buffer)  -- Load image file to buffer.
--	png.load_image(stream,buffer)

	return buffer
end

local function webp_to_png( webp_file, png_file )
--	require("toy.file.export.png").export(png_file,load_image_file("D:/Photos/star.zip", webp_file))
	require("toy.file.export.png").export(png_file,load_image_file("D:/Photos/star",     webp_file))
end

local function main()
	webp_to_png("003.webp","003.png")
end

if bug.catch(main) then
	bug.oops()
end
