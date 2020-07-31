
local text = [===[
{
	"1":"Steven",
	"2":"Johnny",
	"3":"Betty",
	"4":"Molly",
	"5":"沈威"
}
]===]

local msg = require "toy.logger"
local jsn = require "toy.file.io.json"

-- Convert string to table.
local tab = jsn.import(text)

-- Convert table to string.
local str = jsn.export(tab)

msg.print("---------------------------")
require("toy.table").print(tab)
msg.print("---------------------------")
msg.print(str)
msg.print("---------------------------")
