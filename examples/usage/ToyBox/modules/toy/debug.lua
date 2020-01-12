
local bug = require "toy.debug"

local error_happened = true

bug.warn("Error message")    -- Print error message.
bug.oops()                   -- Just highlight current line.

local function main()
	if error_happened then
		bug.quit()                        -- Throw exception.
--		bug.quit("Exception happened")    -- Print message then throw exception.
	end
end

if bug.catch(main) then
	bug.warn("Something wrong")
end
