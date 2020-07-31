
local msg01 = [[
TOY_RESOURCE_PATH_FOR_DEMO is just a string for demo.
Release version doesn't have it.

Declare it again, if you want to show demo in release mode.

For example:
    TOY_RESOURCE_PATH_FOR_DEMO = "d:/ToyBox/resource"
    TOY_RESOURCE_PATH_FOR_DEMO = "~/ToyBox/resource"
]]

--------------------------------------------------------------------------------

if TOY_RESOURCE_PATH_FOR_DEMO==nil then
	print(msg01)
end

--------------------------------------------------------------------------------

-- Set a path for searching your image file, font file, etc.
search_path = TOY_RESOURCE_PATH_FOR_DEMO

-- Set the main script of your project.
script = "main.lua"

-- Set a path for searching main script of project.
  main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/examples/HelloWorld"
--main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/examples/Window"              -- Show a empty window.
--main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/examples/Sound"
--main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/examples/LogSystem"
--main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/examples/SQLite"
--main_path = TOY_RESOURCE_PATH_FOR_DEMO .. "/lua/test"
