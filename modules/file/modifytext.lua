
local   msg = require "toy.logger"
local   bfs = require "toy.path"
local   txt = require "toy.txtio"
local   bug = require "toy.debug"
local   aux = require "toy.file._check"

local function make_sure_folder_ok(target)
	local  path = bfs.create_path(target):parent()

	if bfs.exists(path) then
		if bfs.is_folder(path) then
			if bfs.exists(target) then
				bfs.remove(target)
			end
		else
			bfs.remove(path)
			bfs.build_folder(path)
		end
	else
		bfs.build_folder(path)
	end
end

local function modify_text_line_by_line(source,target,func)
	make_sure_folder_ok(target)

	local   reader = txt.new_reader(source)
	local   writer = txt.new_writer(target)

	repeat
		local   str = reader:next_line()
		if str then
			func(str,function(tt) writer:print(tt) end)
		end
	until ( str==nil )
end

local function modify_text(source,target,func)
	local   ok = false

	if bfs.exists(source) then
		if bfs.is_file(source) then
			if bfs.exists(target) then
				bug.warn("The file already exist:" .. target)
			else
				ok = true
				modify_text_line_by_line(source,target,func)
			end
		else
			bug.quit("It's not a file:" .. source)
		end
	else
		bug.quit("Not found:" .. source)
	end

	if ok==false then
		bug.oops()
	end

	return ok
end

local function check_file( source_file, target_file )
	local ok = true

	if source_file==target_file then
		msg.print("Don't output a file at the same position:" .. source_file)
		bug.oops()
		ok = false
	else
		if bfs.exists(source_file) then
			if not bfs.is_file(source_file) then
				msg.print("It's not a file:" .. source_file)
				bug.oops()
				ok = false
			end
		else
			msg.print("It doesn't exist:" .. source_file)
			bug.oops()
			ok = false
		end

		if bfs.exists(target_file) then
			msg.print("It's already exist:" .. target_file)
			bug.oops()
			ok = false
		end
	end

	return ok
end

-- Prototype:bool(string,string,function)
-- Parameters:
--     1:the source file
--     2:the target file
--     3:a closure
--         Prototype:void(string,function)
--         Parameters:
--             1:input string
--             2:a closure for outputing string to somewhere
--                 Prototype:void(string)
--         Return Values:none
-- Return Values:return false if it failed
local function modify_text_main(source_file,target_file,func)
	if source_file==target_file then
		bug.quit()
	end

	aux.force_remove_file(target_file)

	local ok = true

	if check_file(source_file,target_file) then
		modify_text(source_file,target_file,func)
	else
		ok = false
	end

	return ok
end

return modify_text_main
