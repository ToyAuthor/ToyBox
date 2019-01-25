
local  msg = require "toy.logger"

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

local  window = create_window()

if window:good() then
	-- handleEvent:Mouse event, keyboard event, system event, etc.
	while window:handle_event() do
		window:display()           -- Refresh screen.
	end
else
	msg.print("error:" .. window:error())
end

msg.print("Quit")
