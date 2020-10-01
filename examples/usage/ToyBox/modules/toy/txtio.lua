
local log = require "toy.logger"
local txt = require "toy.txtio"

--------------------------------------------------------------------------------

-- Print target file's content.
local function print_text(filename)
	log.print("File " .. filename .. " start")

	local   reader<close> = txt.new_reader(filename)

	local   str = reader:next_line()   -- Return nil if there is no next line.

	while str do
		log.print(str)
		str = reader:next_line()
	end

	log.print("File " .. filename .. " end")
end

-- Show the content of "log.txt".
print_text("D:/log.txt")

--------------------------------------------------------------------------------

local function make_text(filename)
	local writer<close> = txt.new_writer(filename)

	--[[
	output.txt
	-----------------------------------------
	first line
	-string--string--string--string-
	next line A
	next line B

	next line C
	-----------------------------------------
	]]
	writer:print("first line")
	writer:printf("-string-")
	writer:printf("-string-")
	writer:printf("-string-")
	writer:printf("-string-")
	writer:new_line()
	writer:print("next line A")
	writer:print("next line B")
	writer:new_line()
	writer:print("next line C")
end

-- Make a new text file.
make_text("D:/output.txt")
