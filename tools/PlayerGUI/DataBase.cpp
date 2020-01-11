#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include <toy/Standard.hpp>
#include "DataBase.hpp"

/*
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
#endif*/

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
}

MyDataBase::MyDataBase(const std::string &filename):_filename(filename)
{
	if ( IsFileExist(_filename) )
	{
		boost::property_tree::read_json(_filename,_root);
		RemoveFile(_filename);

		if ( _root.get_child_optional("project_list") )
		{
			for ( auto& v : _root.get_child("project_list") )
			{
				auto& node = v.second;

				_list.push_back(PlayerConfigExt());

				auto i=_list.size()-1;

				_list[i].main_script = node.get("script","");
				_list[i].main_path = node.get("main_path","");
				_list[i].search_path = node.get("resource","");
			}
		}
	}
}

MyDataBase::~MyDataBase()
{
	// Save *.json
	std::fstream    dev;
	dev.open(_filename, std::fstream::in | std::fstream::out | std::fstream::app);
	boost::property_tree::write_json(dev, _root, true);
}

/*
void MyDataBase::getProject()
{
	if ( _root.get_child_optional("project_list") )
	{
		for ( auto& v : _root.get_child("project_list") )
		{
			auto& node = v.second;

			node.get("script","");
			node.get("main_path","");
			node.get("resource","");
		}
	}
}*/

void MyDataBase::setProject(const std::string &script,const std::string &project,const std::string &resource)
{
	boost::property_tree::ptree   data;

	data.put("script",script);
	data.put("main_path",project);
	data.put("resource",resource);

	if ( _root.get_child_optional("project_list") )
	{
		bool isNotFound = true;

		for ( auto& v : _root.get_child("project_list") )
		{
			auto& node = v.second;

			if ( script == node.get("script","") )
			{
				isNotFound = false;
			}
		}

		if ( isNotFound )
		{
			auto& ref = _root.get_child("project_list");

			ref.push_back(std::make_pair("", data));
		}
	}
	else
	{
		boost::property_tree::ptree   list;
		list.push_back(std::make_pair("", data));

		_root.put_child("project_list", list);
	}
}

auto MyDataBase::getProjectList()->std::vector<PlayerConfigExt>&
{
	return _list;
}

/*
auto MyDataBase::getProjectCount()->uint32_t
{
	auto ref = _root.get_child_optional("project_list");

	if ( ref )
	{
		return ref.get().size();
	}

	return 0;
}*/

void MyDataBase::clean()
{
	boost::property_tree::ptree().swap(_root);
//	_root.swap(boost::property_tree::ptree());
}
