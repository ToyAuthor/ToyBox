
local  msg = require "toy.logger"
local  bfs = require "toy.path"

local  logname = "mylog.txt"

if bfs.exists(logname) then
	bfs.remove(logname)
end

msg.as_file(logname)
msg.print("log system日誌系統")
msg.print("ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा")
msg.reset()
msg.print("log system日誌系統")
msg.print("ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा")
