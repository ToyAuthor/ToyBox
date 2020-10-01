
local  log = require "toy.logger"
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

-- [[
local function create_sound()
	local  stream<close> = require("toy.file").create_stream("default")

	stream:open_dir("target_folder")
	stream:open("target_file.wav")

	return snd.new_sound(snd.new_sound_buffer(stream))
end

local function main()
	local  dev = create_sound()

	dev:play()
	log.print("Sound start")
	wait_audio_stop(dev)
	log.print("Sound stop")
end
--]]

--[[
local function main()
	local  dev = snd.new_music("target_folder/target_file.ogg")

	dev:play()
	log.print("Music start")
	wait_audio_stop(dev)
	log.print("Music stop")
end
--]]

if bug.catch(main) then
	bug.oops()
end
