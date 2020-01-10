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

		bool      printable = true;
		sqlite3*  handle = nullptr;
};

static int SQLiteCallback(void *root, int argc, char **argv, char **azColName)
{
	auto   obj = (::toy::sql::DataBasePrivate*)root;

	if ( obj->printable )
	{
		for ( int i=0; i<argc; i++ )
		{
			toy::Logger<<(const char*)(azColName[i])<<" = "<<(const char*)(argv[i] ? argv[i] : "NULL")<<toy::NewLine;
		}

		toy::Logger<<toy::NewLine;
	}

	return 0;
}

DataBase::DataBase(std::string filename):_this(new DataBasePrivate)
{
	if ( SQLITE_OK != sqlite3_open(filename.c_str(), &(_this->handle)) )
	{
		toy::Logger<<sqlite3_errmsg(_this->handle)<<toy::NewLine;
		throw toy::Exception(TOY_MARK);
	}
}

void DataBase::cmd(std::string cmd)
{
	char *errMsg = nullptr;

	if( SQLITE_OK != sqlite3_exec(_this->handle, cmd.c_str(), SQLiteCallback, (void*)_this.get(), &errMsg) )
	{
		toy::Logger<<"SQLite error:"<<errMsg<<toy::NewLine;
		sqlite3_free(errMsg);
	}
}

void DataBase::printable(bool flag)
{
	_this->printable = flag;
}

DataBase::~DataBase()
{
	sqlite3_close(_this->handle);
}

}}
