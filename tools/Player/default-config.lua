
local msg01 = [[
Toy_ResourcePathForDemo is just a string for demo.
Release version doesn't has it.

Declare it again, if you want to show demo in release mode.

For example:
    Toy_ResourcePathForDemo = "d:/lua/projects/resource"
]]

--------------------------------------------------------------------------------

if Toy_ResourcePathForDemo==nil then
	print(msg01)
end

--------------------------------------------------------------------------------

-- Set a path for searching your image file ... etc.
search_path = Toy_ResourcePathForDemo

-- Set the main script of your project.
script = "main.lua"

-- Set a path for searching main script of project.
main_path = Toy_ResourcePathForDemo .. "/lua/examples/HelloWorld"
--main_path = Toy_ResourcePathForDemo .. "/lua/examples/Window"              -- Show a empty window.
