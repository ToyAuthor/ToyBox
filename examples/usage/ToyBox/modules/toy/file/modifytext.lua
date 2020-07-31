
local modify_text  = require "toy.file.modifytext"

local function func( origin_string, print_to_text_file )
	print_to_text_file(origin_string .. "__addition")
end

-- Read "text1.txt" then make a new file "text2.txt".
-- It would not modify "text1.txt".
modify_text("D:/text1.txt","D:/text2.txt",func)

--[[



text1.txt
-----------------------------------------
data
apple
star
-----------------------------------------



text2.txt
-----------------------------------------
data__addition
apple__addition
star__addition
-----------------------------------------



]]
