
local  msg = require "toy.logger"
local  sql = require "toy.sql"
local  bug = require "toy.debug"

local function main()
	local dev = sql.open("mydatabase.db")

	dev:cmd( [[ CREATE TABLE COMPANY( ID         INT        PRIMARY KEY     NOT NULL,
	                                  NAME       TEXT                       NOT NULL,
	                                  AGE        INT                        NOT NULL,
	                                  ADDRESS    CHAR(50),
	                                  SALARY     REAL);      ]] )

	dev:cmd("INSERT INTO COMPANY VALUES (1, 'James', 24, 'Houston', 10000.00 );" )

	local callback_func = function(name,value)
		msg.print(name .. ":" .. value)
	end

	dev:cmd("SELECT * FROM COMPANY;",callback_func)

--	dev:fuss(true)          -- Call lua_error() when any error happened. It's default setting.
--	dev:fuss(false)         -- Let dev.cmd() return false when error happened.

	if dev:fuss() then
		msg.print("You just set dev:fuss(true)")
	else
		msg.print("You just set dev:fuss(false)")
	end

	if false==dev:cmd("INSERT INTO COMPANY VALUES (1, 'James', 24, 'Houston', 10000.00 );",callback_func) then
		msg.print("Error message from SQLite:" .. dev:error_msg())
	end
end

if bug.catch(main) then
	bug.oops()
end
