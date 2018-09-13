
local  msg = require "toy.logger"

local function CreateWindow()

	local  config =
	{
		title = "Sample window;範例視窗",
		width = 800,
		height = 600,
	}

	return require("toy.window").createWindow(config)
end

msg.print("Starting")

local  window = CreateWindow()

if window:good() then
	-- handleEvent:Mouse event, keyboard event, system event, etc.
	while window:handleEvent() do
		window:display()           -- Refresh screen.
	end
else
	msg.print("error:" .. window:error())
end

msg.print("Quit")
