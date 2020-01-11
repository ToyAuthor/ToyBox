
#pragma once

#include <memory>
#include <string>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>

class Interface;

struct PlayerConfigExt
{
	std::string    main_path;                // It's a path of main script, and a search path too.
	std::string    search_path;              // It's a search path for searching common scripts or resource ...etc.
	std::string    main_script = "main.lua";
	Interface*     boss = nullptr;
};

class MyDataBase
{
	public:

		MyDataBase(const std::string &filename);
		~MyDataBase();

		void setProject(const std::string &script,const std::string &project,const std::string &resource);
		void clean();
		auto getProjectList()->std::vector<PlayerConfigExt>&;

	private:

		boost::property_tree::ptree      _root;
		const std::string                _filename;
		std::vector<PlayerConfigExt>     _list;
};
