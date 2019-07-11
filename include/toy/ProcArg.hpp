
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include "toy/Exception.hpp"

namespace toy{

class ProcArg
{
	public:

		ProcArg(int argc, char** argv, std::string tag1="-",std::string tag2=std::string(),std::string tag3=std::string())
		{
			if ( argc==0 )
			{
				throw toy::Exception(TOY_MARK);
			}

			if ( argc==1 )
			{
				return;
			}

			std::string str;
			std::string group("");

			for ( int i=1 ; i<argc ; i++ )
			{
				str = argv[i];

				if ( (                  str.substr(0,tag1.size())==tag1 ) ||
				     ( !tag2.empty() && str.substr(0,tag2.size())==tag2 ) ||
				     ( !tag3.empty() && str.substr(0,tag3.size())==tag3 ) )
				{
					group = str;

					if ( _data.find(group) == _data.end() )
					{
						_tags.push_back(group);
						_data[group] = std::make_shared<std::vector<std::string>>();
					}
					continue;
				}

				if ( _data.find(group) == _data.end() )
				{
					_tags.push_back("");
					_data[""] = std::make_shared<std::vector<std::string>>();
				}

				_data[group]->push_back(str);
			}
		}

		~ProcArg(){}

		auto operator [](const std::string &str) const -> std::shared_ptr<const std::vector<std::string>>
		{
			const auto it = _data.find(str);

			if ( it == _data.end() )
			{
				return nullptr;
			}

			return it->second;
		}

		auto tags() const -> const std::vector<std::string> &
		{
			return _tags;
		}

	private:

		std::vector<std::string>                                         _tags;
		std::map<std::string,std::shared_ptr<std::vector<std::string>>>  _data;
};

}
