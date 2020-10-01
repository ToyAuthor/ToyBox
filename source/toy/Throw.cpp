#include <stdexcept>
#include <string>
#include "toy/MarkString.hpp"
#include "toy/Throw.hpp"
#include "toy/Catch.hpp"
#include "toy/Log.hpp"
#include "toy/Oops.hpp"

#define TOY_ERROR_MESSAGE_PREFIX "toyexception:"

void ::toy::Throw(const char *file,int line, enum ::toy::ErrorTag tag)
{
	std::string         str(TOY_ERROR_MESSAGE_PREFIX);
	str.push_back(static_cast<char>(tag));
	str.push_back(':');

	throw std::runtime_error(str + toy::MarkString(file,line));
}

auto ::toy::Catch(std::exception &e)-> enum ::toy::ErrorTag
{
	enum ::toy::ErrorTag   tag;
	std::string            str(TOY_ERROR_MESSAGE_PREFIX);

	if ( std::string(e.what(),str.size())==str )
	{
		toy::Log(e);

		const char  id = *(e.what()+str.size());

		if ( id=='\0' )
		{
			toy::Oops(TOY_MARK);
			throw;
		}
		else
		{
			tag = (enum ::toy::ErrorTag)id;
		}
	}
	else
	{
		throw;
	}

	return tag;
}

auto ::toy::Catch_ForTest(std::exception &e)-> enum ::toy::ErrorTag
{
	enum ::toy::ErrorTag   tag;
	std::string            str(TOY_ERROR_MESSAGE_PREFIX);

	if ( std::string(e.what(),str.size())==str )
	{
		const char  id = *(e.what()+str.size());

		if ( id=='\0' )
		{
			throw;
		}
		else
		{
			tag = (enum ::toy::ErrorTag)id;
		}
	}
	else
	{
		throw;
	}

	return tag;
}
