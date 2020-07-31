
local  msg  = require "toy.logger"
local  bug  = require "toy.debug"
local  sys  = require "toy.root"
local  file = require "toy.file"
local  webp = require "toy.file.loader.webp"

local function create_window()
	local  config =
	{
		title = "Show a webp image",
		width = 800,
		height = 600,
	}

	return require("toy.graph").create_window(config)
end

local function load_image_file(folder,filename)
	local  stream = file.create_stream("default")
	local  buffer = file.create_image_buffer()

	stream:open_dir(folder)
	stream:open(filename)
	webp.load_image(stream,buffer)     -- Load data from stream, then put into the buffer.

	return buffer
end

local function main()
	local  window = create_window()
	local  image  = window:create_scene():new_image(load_image_file("D:/projects/ToyBox/resource","002.webp"))

	image:visible(true)
	image:set_position(-400,-300)

	while window:handle_event() do
		window:display()
	end
end

if bug.catch(main) then
	bug.oops()
end
