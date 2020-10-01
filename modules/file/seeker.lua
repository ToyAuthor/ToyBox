
local   bfs = require "toy.path"
local   txt = require "toy.txtio"
local   bug = require "toy.debug"
local   rex = require "toy.regex"
local   msg = require "toy.logger"

local   view_folder = require "toy.file.visitfolder"

local function set_default_value_to_undefine_option(config)
	if type(config.ignore_new_line_character ) ~="boolean"   then config.ignore_new_line_character    = true  end
	if type(config.only_search_one_line      ) ~="boolean"   then config.only_search_one_line         = false end
	if type(config.one_file_one_report       ) ~="boolean"   then config.one_file_one_report          = false end
end

local function reader_loop_for_one_line(name,word,reader,config)
	local line_number = 0

	local function for_regex(str,index,length)
		-- do nothing
	end

	repeat
		local   str = reader:next_line()
		line_number = line_number+1

		if str then
			local temp_str

			if config.ignore_new_line_character==false then
				temp_str = str .. "\n"
			else
				temp_str = str
			end

			if rex.search(word,temp_str,for_regex) then
				msg.print(name .. " " .. line_number .. ":" .. str)

				if config.one_file_one_report then
					str = nil
				end
			end
		end
	until ( str==nil )
end

local function reader_loop_for_two_line(name,word,reader,config)
	local line_number = 0
	local previous_word = ""
	local complete_match = false
	local partial_match = false

	local function for_regex(str,is_match,index,length)
		if is_match==true then
			complete_match = true
			previous_word = ""
		else
			partial_match = true
			previous_word = previous_word .. str
		end
	end

	repeat
		local   str    = reader:next_line()
		line_number    = line_number+1
		partial_match  = false
		complete_match = false

		if str then
			local temp_str

			if config.ignore_new_line_character==false then
				temp_str = str .. "\n"
			else
				temp_str = str
			end

			if rex.recur_search_partial(word,previous_word .. temp_str,for_regex) then
				if partial_match==false then
					previous_word = ""
				end

				if complete_match then
					msg.print(name .. " " .. line_number .. ":" .. str)

					if config.one_file_one_report then
						str = nil
					end
				end
			else
				previous_word = ""
			end
		end
	until ( str==nil )
end

local function find_word_in_folder(word,folder,config)
	if config==nil then
		config = {}
	end

	if type(config)~="table" then
		bug.warn("wrong config in seeker")
		config = {}
	end

	set_default_value_to_undefine_option(config)

	if bfs.is_folder(folder) then
		local   reader = 0

		local function view_it(name)
			if reader==0 then
				reader = txt.new_reader(name)
			else
				reader:open(name)
			end

			if config.only_search_one_line then
				reader_loop_for_one_line(name,word,reader,config)
			else
				reader_loop_for_two_line(name,word,reader,config)
			end
		end

		view_folder(folder,view_it)
	else
		bug.error("It's not a folder:" .. name)
	end
end

local function find_word_in_file(word,file_name,config)
	if config==nil then
		config = {}
	end

	if type(config)~="table" then
		bug.warn("wrong config in seeker")
		config = {}
	end

	set_default_value_to_undefine_option(config)

	if bfs.is_file(file_name) then
		local   reader<close> = txt.new_reader(file_name)

		if config.only_search_one_line then
			reader_loop_for_one_line(file_name,word,reader,config)
		else
			reader_loop_for_two_line(file_name,word,reader,config)
		end
	else
		bug.error("It's not a file:" .. file_name)
	end
end

return
{
	find_word_in_folder = find_word_in_folder,
	find_word_in_file   = find_word_in_file,
}
