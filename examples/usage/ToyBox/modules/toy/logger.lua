
local  log = require "toy.logger"

local  utf_str<const> = "log system日誌系統"

--------------------------------------------------------------------------------

log.printf(utf_str)  -- Print message without new line.
log.print(utf_str)   -- Print message with new line.

--------------------------------------------------------------------------------

if log.is_utf8(utf_str) then
	log.print("It's utf-8 encode")
else
	log.print("It's not utf-8 encode")
end

--------------------------------------------------------------------------------

log.as_file("mylog.txt")   -- The following message will be saved to the given file.
log.print("log 1")
log.print("log 2")
log.print("log 3")
log.reset()                -- Resume to default status.
