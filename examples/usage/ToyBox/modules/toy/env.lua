-- More information
-- ToyBox/modules/ext/Env/*.cpp

local  env = require "toy.env"
local  ver = env.get_player_version()

print("Operating System:" .. env.os())
print("Compiler        :" .. env.compiler())
print("Player version  :" .. ver.major .. "." .. ver.minor .. "." .. ver.patch)
