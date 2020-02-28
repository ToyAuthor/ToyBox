
#pragma once

#include <memory>
#include <string>
#include <functional>
#include "toy/sql/Export.hpp"

namespace toy{
namespace sql{

class DataBasePrivate;

class TOY_API_SQLITE DataBase
{
	public:

		struct Config
		{
			bool   printable = false;     // Always output message by toy::Logger
			bool   fuss = false;          // Throw exception if DataBase::cmd happen error.
		};

		DataBase();
		DataBase(const std::string &filename);
		~DataBase();

		bool open(const std::string &filename);
		void close();
		bool empty();
		void config(::toy::sql::DataBase::Config*) const;
		void config(const ::toy::sql::DataBase::Config &);
		bool cmd(std::string cmd,std::function<void(std::string,std::string)> func={});
		auto error()->std::string;    // Output the latest error message.

	private:

		std::unique_ptr<DataBasePrivate>   _this;
};

}}
