
#pragma once

#include <memory>
#include <vector>
#include "PlayerConfig.hpp"
#include "DataBase.hpp"

class Fl_Input;
class Fl_Window;
struct Fl_Menu_Item;

class Interface
{
	public:

		Interface(PlayerConfig*);
		~Interface();

		void run();
		bool isGetConfig();
		Fl_Menu_Item* getMenu();

//	private:

		PlayerConfig*                       _config;
		std::unique_ptr<Fl_Window>          _window;
		Fl_Input*                           _input;
		Fl_Input*                           _script;
		Fl_Input*                           _resource;
		bool                                _isGetConfig = false;
		MyDataBase                          _database;
		std::vector<Fl_Menu_Item>           _item;
};
