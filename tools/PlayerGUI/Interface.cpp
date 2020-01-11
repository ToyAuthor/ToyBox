#include <fstream>
#include <FL/Fl.H>
#include <FL/fl_ask.H>		// fl_beep()
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "toy/Standard.hpp"
#include "toy/Utf.hpp"
#include "Interface.hpp"

#ifdef TOY_WINDOWS
	static inline boost::filesystem::path StrToPath(std::string str)
	{
		return boost::filesystem::path(toy::utf::UTF8ToWChar(str));
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return toy::utf::WCharToUTF8(str.wstring());
	}
#else
	static inline boost::filesystem::path StrToPath(std::string str)
	{
		return boost::filesystem::path(str);
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return str.string();
	}
#endif
/*
static inline bool IsFileExist(const std::string &filename)
{
	#ifdef TOY_WINDOWS
		return boost::filesystem::exists( toy::utf::UTF8ToWChar(filename) );
	#else
		return boost::filesystem::exists( filename );
	#endif

		return true;
}

static inline void RemoveFile(const std::string &filename)
{
	#ifdef TOY_WINDOWS
		boost::filesystem::remove( toy::utf::UTF8ToWChar(filename) );
	#else
		boost::filesystem::remove( filename );
	#endif
}*/

static void Window_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	obj->_window->hide();
//	obj->_window->iconize();
}

static void TryToRun_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	std::string name = obj->_script->value();
	std::string dir  = obj->_input->value();
	std::string res  = obj->_resource->value();

	if ( name.empty() )
	{
		fl_beep();
		fl_alert("Entry could not be empty");
	}
	else
	{
		if ( boost::filesystem::exists(name) )
		{
			obj->_config->main_path = dir;
			obj->_config->search_path = res;
			obj->_config->main_script = PathToStr(StrToPath(name).filename());
			obj->_database.setProject(name,dir,res);
			obj->_isGetConfig = true;
			obj->_window->hide();
		}
		else
		{
			fl_beep();
			fl_alert("%s",(std::string("File ") + name + " doesn't exist").c_str());
	//		fl_message((std::string("File ") + name + " doesn't exist").c_str());
	//		fl_ask((std::string("File ") + name + " doesn't exist").c_str());
		}
	}
}

static void QuitApp_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	obj->_window->hide();
}

static void PickDir_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	// Create native chooser
	Fl_Native_File_Chooser native;
	native.title("Pick a directory");
	native.directory(obj->_input->value());
	native.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
//	native.type(Fl_Native_File_Chooser::BROWSE_FILE);

	switch ( native.show() )
	{
		case -1:
		{
			toy::Logger<<"ERROR: "<<native.errmsg()<<toy::NewLine;
			break;
		}

		case  1:
		{
		//	toy::Logger<<"*** CANCEL"<<toy::NewLine;
			break;
		}

		default:
		{
			if ( native.filename() )
			{
				auto dir = StrToPath(native.filename());

				obj->_input->value(native.filename());

				auto filename = dir/"main.lua";

				if ( boost::filesystem::exists(filename) )
				{
					obj->_script->value(PathToStr(filename).c_str());
				}
			}
			else
			{
				obj->_input->value("NULL");
			}
			break;
		}
	}
}

static void PickScript_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	// Create native chooser
	Fl_Native_File_Chooser native;
	native.title("Pick a file");
	native.preset_file(obj->_script->value());
	native.type(Fl_Native_File_Chooser::BROWSE_FILE);

	switch ( native.show() )
	{
		case -1:
		{
			toy::Logger<<"ERROR: "<<native.errmsg()<<toy::NewLine;
			break;
		}

		case  1:
		{
		//	toy::Logger<<"*** CANCEL"<<toy::NewLine;
			break;
		}

		default:
		{
			if ( native.filename() )
			{
				obj->_script->value(native.filename());

				auto filename = StrToPath(native.filename());

				auto par = PathToStr(filename.parent_path());

				if ( ! par.empty() )
				{
					obj->_input->value(par.c_str());
				}
			}
			else
			{
				obj->_script->value("NULL");
			}
			break;
		}
	}
}

static void PickResourcePath_CB(Fl_Widget*, void *objv)
{
	auto obj = (Interface*)objv;

	// Create native chooser
	Fl_Native_File_Chooser native;
	native.title("Pick a directory");
	native.directory(obj->_resource->value());
	native.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);

	switch ( native.show() )
	{
		case -1:
		{
			toy::Logger<<"ERROR: "<<native.errmsg()<<toy::NewLine;
			break;
		}

		case  1:
		{
		//	toy::Logger<<"*** CANCEL"<<toy::NewLine;
			break;
		}

		default:
		{
			if ( native.filename() )
			{
				obj->_resource->value(native.filename());
			}
			else
			{
				obj->_resource->value("NULL");
			}
			break;
		}
	}
}

static void ChoiceCb(Fl_Widget*, void *vi)
{
	auto obj = (PlayerConfigExt*)vi;

	obj->boss->_script->value(obj->main_script.c_str());
	obj->boss->_input->value(obj->main_path.c_str());
	obj->boss->_resource->value(obj->search_path.c_str());
}

Fl_Menu_Item* Interface::getMenu()
{
	std::vector<PlayerConfigExt>  &json = _database.getProjectList();

	_item.resize(json.size()+1);

	memset(_item.data(), 0, sizeof(Fl_Menu_Item)*_item.size());

	for(auto i=_item.size()-1;i>0;)
	{
		i--;
		json[i].boss = this;
		_item[i].text = json[i].main_script.c_str();
		_item[i].callback_ = ChoiceCb;
	//	_item[i].user_data_ = (void*)(json.data()+i);
		_item[i].user_data_ = (void*)(&(json[i]));
	}

	return _item.data();
}

Interface::Interface(PlayerConfig *config):_config(config),_database("player-gui.json")
{
//	Fl::scheme("plastic");
	Fl::scheme("gtk+");

	_window.reset(new Fl_Window(555,290,"Player v0.1.0"));

	// See ToyBox/doc/extlibs/fltk/fltk-colormap.png
	_window->color(54);
	_window->callback(Window_CB,this);
	_window->size_range(_window->w(), _window->h(), 0, 0);

	_window->begin();
	{
		_script = new Fl_Input(100, 10, 350, 25, "*Entry");
		_input = new Fl_Input(100, 40, 350, 25, "*Project Path");
		_resource = new Fl_Input(100, 70, 350, 25, "Resource");

	//	_window->resizable(new Fl_Box(FL_FRAME_BOX, 100, 100, 20, 50, 0));
		_window->resizable(new Fl_Box(FL_NO_BOX, 100, 100, 20, 50, 0));

		//----------------------------------------------------------------------

		auto butscr = new Fl_Button(460, 10, 60, 25, "Open");

		butscr->color(_window->color());

		butscr->callback(PickScript_CB,this);

		//----------------------------------------------------------------------

		auto butdir = new Fl_Button(460, 40, 60, 25, "Open");

		butdir->color(_window->color());

		butdir->callback(PickDir_CB,this);

		//----------------------------------------------------------------------

		auto butrsc = new Fl_Button(460, 70, 60, 25, "Open");

		butrsc->color(_window->color());

		butrsc->callback(PickResourcePath_CB,this);

		//----------------------------------------------------------------------

		auto tryToRun = new Fl_Button(370, 250, 80, 25, "Run");

		tryToRun->color(_window->color());

		tryToRun->callback(TryToRun_CB,this);

		//----------------------------------------------------------------------

		auto quitButton = new Fl_Button(460, 250, 80, 25, "Quit");

		quitButton->color(_window->color());

		quitButton->callback(QuitApp_CB,this);

		//----------------------------------------------------------------------

		if ( _database.getProjectList().size()>0 )
		{
			auto history = new Fl_Choice(100,150,350,25,"History");
			history->menu(getMenu());
			history->when(FL_WHEN_RELEASE|FL_WHEN_NOT_CHANGED);
			history->color(_window->color());
		}
	}
	_window->end();
}

Interface::~Interface()
{
	;
}

bool Interface::isGetConfig()
{
	return _isGetConfig;
}

void Interface::run()
{
	_window->show();

	while(Fl::wait())
	{
		;
	}
}
