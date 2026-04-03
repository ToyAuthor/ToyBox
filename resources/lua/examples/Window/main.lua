
local  msg = require "toy.logger"
local  bug = require "toy.debug"

local function create_window()

	local  config =
	{
		title = "Sample window;範例視窗",
		width = 800,
		height = 600,
	}

	return require("toy.window").create_window(config)
end

msg.print("Starting")

local function main()
	local  window = create_window()

	-- handleEvent:Mouse event, keyboard event, system event, etc.
	while window:handle_event() do
		window:display()           -- Refresh screen.
	end
end

if bug.catch(main) then
	bug.oops()
end

msg.print("Quit")
