#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/path/Status.hpp>
#include <toy/sql/DataBase.hpp>

static void PrintMsg(std::string a,std::string b)
{
	toy::Logger<<a<<" = "<<b<<toy::NewLine;
}

static int main2()
{
	toy::sql::DataBase   dev("database.db");

	{
		toy::sql::DataBase::Config   config;
		config.printable = false;
		config.fuss = true;
		dev.config(config);
	}

	dev.cmd( R"(CREATE TABLE COMPANY( ID         INT        PRIMARY KEY     NOT NULL,
	                                  NAME       TEXT                       NOT NULL,
	                                  AGE        INT                        NOT NULL,
	                                  ADDRESS    CHAR(50),
	                                  SALARY     REAL);)" );

	dev.cmd("INSERT INTO COMPANY VALUES (1, 'James', 24, 'Houston', 10000.0 );" );

	dev.cmd("SELECT * FROM COMPANY;",PrintMsg);

	return EXIT_SUCCESS;
}

int main()
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2();
	}
	catch(std::exception &e)
	{
		toy::Log(e);
	}

	return result;
}
