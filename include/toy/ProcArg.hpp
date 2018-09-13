
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

		ProcArg(int argc, char** argv, char tagHead='-')
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

				if ( str[0]==tagHead )
				{
					group = str;

					if ( _data.find(group) == _data.end() )
					{
						_data[group] = std::make_shared<std::vector<std::string>>();
					}
					continue;
				}

				if ( _data.find(group) == _data.end() )
				{
					_data[group] = std::make_shared<std::vector<std::string>>();
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

	private:

		std::map<std::string,std::shared_ptr<std::vector<std::string>>>  _data;
};

}
