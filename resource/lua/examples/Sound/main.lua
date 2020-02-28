
local  msg = require "toy.logger"
local  snd = require "toy.audio"
local  tim = require "toy.time"
local  bfs = require "toy.path"
local  sys = require "toy.root"
local  bug = require "toy.debug"

local function wait_audio_stop(dev)
	while dev:is_playing() do
		tim.sleep(0.1)
	end
end

local function create_sound()
	local  stream = require("toy.file").create_stream("7zip")

	stream:open_dir(sys.get_resource_path() .. "/package.7z")
	stream:open("canary.wav")

	return snd.new_sound(snd.new_sound_buffer(stream))
end

local function main()
	local  dev = create_sound()

	dev:play()
	msg.print("Sound start")
	wait_audio_stop(dev)
	msg.print("Sound stop")
end

if bug.catch(main) then
	bug.oops()
end
