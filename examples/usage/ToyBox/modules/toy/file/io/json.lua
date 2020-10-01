
local text = [===[
{
	"1":"Steven",
	"2":"Johnny",
	"3":"Betty",
	"4":"Molly",
	"5":"沈威"
}
]===]

local log = require "toy.logger"
local jsn = require "toy.file.io.json"

-- Convert string to table.
local tab = jsn.import(text)

-- Convert table to string.
local str = jsn.export(tab)

log.print("---------------------------")
require("toy.table").print(tab)
log.print("---------------------------")
log.print(str)
log.print("---------------------------")
