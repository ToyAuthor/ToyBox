
local  sys = require "toy.root"
local  eye = require "toy.file.seeker"

local  config = {}
config.one_file_one_report = false
config.only_search_one_line = false
config.ignore_new_line_character = false

eye.find_word_in_file("key word",sys.get_project_path() .. "target file")
eye.find_word_in_file("key word",sys.get_project_path() .. "target file",config)
eye.find_word_in_folder("key word",sys.get_project_path() .. "target folder")
eye.find_word_in_folder("key word",sys.get_project_path() .. "target folder",config)
