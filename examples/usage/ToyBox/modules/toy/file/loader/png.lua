
local  bug = require "toy.debug"
local  fs  = require "toy.file"
local  png = require "toy.file.loader.png"

local function create_window()
	local  config =
	{
		title = "Show a png image",
		width = 800,
		height = 600,
	}

	return require("toy.graph").create_window(config)
end

local function load_image_file(folder,filename)
	local  stream = fs.create_stream("default")
	local  buffer = fs.create_image_buffer()

	stream:open_dir(folder)
	stream:open(filename)
	png.load_image(stream,buffer)     -- Load data from stream, then put into the buffer.

	return buffer
end

local function main()
	local  window = create_window()
	local  image  = window:create_scene():new_image(load_image_file("D:/projects/ToyBox/resource","002.png"))

	image:visible(true)
	image:set_position(-400,-300)

	while window:handle_event() do
		window:display()
	end
end

if bug.catch(main) then
	bug.oops()
end
