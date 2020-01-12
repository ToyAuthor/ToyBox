
local  msg = require "toy.logger"

--------------------------------------------------------------------------------

msg.printf("log system日誌系統")  -- Print message without new line.
msg.print("log system日誌系統")   -- Print message with new line.

--------------------------------------------------------------------------------

if msg.is_utf8("ansi key code") then
	msg.print("It's utf-8 encode")
else
	msg.print("It's not utf-8 encode")
end

--------------------------------------------------------------------------------

msg.as_file("mylog.txt")   -- The following message will be saved to the given file.
msg.print("log 1")
msg.print("log 2")
msg.print("log 3")
msg.reset()                -- Resume to default status.
