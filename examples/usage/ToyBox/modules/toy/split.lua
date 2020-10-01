
local log = require "toy.logger"

local splitter = require("toy.split").create_splitter()

--splitter:load   ("D:/projects/ToyBox/include/toy/Standard.hpp"        )       -- Output B
--splitter:load_ex("D:/projects/ToyBox/include/toy/Standard.hpp","right")       -- Output B
  splitter:load_ex("D:/projects/ToyBox/include/toy/Standard.hpp","left" )       -- Output A
  splitter:push_config( { break_char = {"/"} } )

local str = splitter:next()   -- Return nil if no next token exist.

while str do
	log.print("str:" .. str)
	str = splitter:next()
end

--[====================[

Output A:

Standard.hpp
/
toy
/
include
/
ToyBox
/
projects
/
D:

------------------------------------------

Output B:

D:
/
projects
/
ToyBox
/
include
/
toy
/
Standard.hpp

]====================]
