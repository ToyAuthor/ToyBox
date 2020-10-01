
local log = require "toy.logger"
local tim = require "toy.time"

--------------------------------------------------------------------------------

tim.sleep(0.1)    -- Sleep 0.1 seconds

--------------------------------------------------------------------------------

local timer = tim.new_timer()

timer:restart()    -- Start to counting

tim.sleep(10)

log.print(timer:restart() .. " seconds has been passed.")   -- Recounting

tim.sleep(10)

log.print(timer:passed() .. " seconds has been passed.")    -- No recount

tim.sleep(10)

log.print(timer:passed() .. " seconds has been passed.")

--[[
Output:
---------------------------------
10.0 seconds has been passed.
10.0 seconds has been passed.
20.0 seconds has been passed.
---------------------------------
]]
