
#pragma once

#include <memory>
#include <string>
#include "toy/sql/Export.hpp"

namespace toy{
namespace sql{

class DataBasePrivate;

class TOY_API_SQLITE DataBase
{
	public:

		DataBase(std::string filename);
		~DataBase();

		void cmd(std::string cmd);
		void printable(bool flag=true);

	private:

		std::unique_ptr<DataBasePrivate>   _this;
};

}}
