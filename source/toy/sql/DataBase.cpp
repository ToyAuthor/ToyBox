#include <sqlite3.h>
#include "toy/Exception.hpp"
#include "toy/Log.hpp"
#include "toy/sql/DataBase.hpp"

namespace toy{
namespace sql{

class DataBasePrivate
{
	public:

		DataBasePrivate(){}
		~DataBasePrivate(){}

		sqlite3*       handle = nullptr;
		std::string    error_message = "no error";
		std::function<void(std::string,std::string)>   reaction = {};

		bool     printable = false;
		bool     fuss = false;
};

static int SQLiteCallback(void *root, int argc, char **argv, char **azColName)
{
	auto   obj = (::toy::sql::DataBasePrivate*)root;

	if ( obj->printable )
	{
		for ( int i=0; i<argc; i++ )
		{
			toy::Logger<<azColName[i]<<" = "<<(const char*)(argv[i] ? argv[i] : "NULL")<<toy::NewLine;
		}
	}
	else if ( obj->reaction )
	{
		for ( int i=0; i<argc; i++ )
		{
			(obj->reaction)(azColName[i],(const char*)(argv[i] ? argv[i] : "NULL"));
		}
	}

	return 0;
}

DataBase::DataBase():_this(new DataBasePrivate)
{
	;
}

DataBase::DataBase(const std::string &filename):_this(new DataBasePrivate)
{
	if ( ! open(filename) )
	{
		throw toy::Exception(TOY_MARK);
	}
}

DataBase::~DataBase()
{
	close();
}

bool DataBase::open(const std::string &filename)
{
	close();

	if ( SQLITE_OK != sqlite3_open(filename.c_str(), &(_this->handle)) )
	{
		_this->error_message = sqlite3_errmsg(_this->handle);
		if ( _this->printable ) toy::Logger<<_this->error_message<<toy::NewLine;
		_this->handle = nullptr;    // Just in case
		return false;
	}

	return true;
}

void DataBase::close()
{
	if ( _this->handle )
	{
		sqlite3_close(_this->handle);
		_this->handle = nullptr;
	}
}

bool DataBase::empty()
{
	return (_this->handle==nullptr) ? true:false;
}

std::string DataBase::error()
{
	return _this->error_message;
}

void DataBase::config(::toy::sql::DataBase::Config *config) const
{
	config->printable = _this->printable;
	config->fuss = _this->fuss;
}

void DataBase::config(const ::toy::sql::DataBase::Config &config)
{
	_this->printable = config.printable;
	_this->fuss = config.fuss;
}

bool DataBase::cmd(std::string cmd,std::function<void(std::string,std::string)> func)
{
	if ( empty() )
	{
		_this->error_message = "database not found";
		if ( _this->printable ) toy::Logger<<_this->error_message<<toy::NewLine;
		return false;
	}

	char *errMsg = nullptr;

	_this->reaction = func;

	if( SQLITE_OK != sqlite3_exec(_this->handle, cmd.c_str(), SQLiteCallback, (void*)_this.get(), &errMsg) )
	{
		_this->error_message = errMsg;
		if ( _this->fuss ) throw toy::Exception(TOY_MARK);
		if ( _this->printable ) toy::Logger<<_this->error_message<<toy::NewLine;

		sqlite3_free(errMsg);
		return false;
	}

	return true;
}

}}
