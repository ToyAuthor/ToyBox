
#pragma once

#include <string>

// I must separate path and script name. They can't be a single string.
struct PlayerConfig
{
	std::string    main_path;                // It's a path of main script, and a search path too.
	std::string    search_path;              // It's a search path for searching common scripts or resource ...etc.
	std::string    main_script = "main.lua";
};
