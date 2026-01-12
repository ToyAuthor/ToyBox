#include "toy/canvas/Standard.hpp"
#include "toy/canvas/CheckVersion.hpp"

namespace toy{
namespace canvas{

struct GraphVersionList
{
	GraphVersionList(enum toy::Option ver,std::string verstr):version(ver),str(verstr){}
	GraphVersionList(){}

	enum toy::Option  version = toy::NOTHING;
	std::string       str     = "Unknown";
};

#if TOY_OPTION_USE_GLEW
static inline std::shared_ptr<std::vector<GraphVersionList>> GetVersionSupportedList()
{
	auto  list = std::make_shared<std::vector<GraphVersionList>>();

	if( GLEW_VERSION_4_5 )
	{
		list->push_back(GraphVersionList(toy::GL_4_5,"4.5"));
	}

	if( GLEW_VERSION_4_4 )
	{
		list->push_back(GraphVersionList(toy::GL_4_4,"4.4"));
	}

	if( GLEW_VERSION_4_3 )
	{
		list->push_back(GraphVersionList(toy::GL_4_3,"4.3"));
	}

	if( GLEW_VERSION_4_2 )
	{
		list->push_back(GraphVersionList(toy::GL_4_2,"4.2"));
	}

	if( GLEW_VERSION_4_1 )
	{
		list->push_back(GraphVersionList(toy::GL_4_1,"4.1"));
	}

	if( GLEW_VERSION_4_0 )
	{
		list->push_back(GraphVersionList(toy::GL_4_0,"4.0"));
	}

	if( GLEW_VERSION_3_3 )
	{
		list->push_back(GraphVersionList(toy::GL_3_3,"3.3"));
	}

	if( GLEW_VERSION_3_2 )
	{
		list->push_back(GraphVersionList(toy::GL_3_2,"3.2"));
	}

	if( GLEW_VERSION_3_1 )
	{
		list->push_back(GraphVersionList(toy::GL_3_1,"3.1"));
	}

	if( GLEW_VERSION_3_0 )
	{
		list->push_back(GraphVersionList(toy::GL_3_0,"3.0"));
	}

	if( GLEW_VERSION_2_1 )
	{
		list->push_back(GraphVersionList(toy::GL_2_1,"2.1"));
	}

	if( GLEW_VERSION_2_0 )
	{
		list->push_back(GraphVersionList(toy::GL_2_0,"2.0"));
	}

	if( GLEW_VERSION_1_5 )
	{
		list->push_back(GraphVersionList(toy::GL_1_5,"1.5"));
	}

	if( GLEW_VERSION_1_4 )
	{
		list->push_back(GraphVersionList(toy::GL_1_4,"1.4"));
	}

	if( GLEW_VERSION_1_3 )
	{
		list->push_back(GraphVersionList(toy::GL_1_3,"1.3"));
	}

	if( GLEW_VERSION_1_2 )
	{
		list->push_back(GraphVersionList(toy::GL_1_2,"1.2"));
	}

	if( GLEW_VERSION_1_1 )
	{
		list->push_back(GraphVersionList(toy::GL_1_1,"1.1"));
	}

	if ( list->empty() )
	{
		list->push_back(GraphVersionList());
	}

	return list;
}
#else
static inline std::shared_ptr<std::vector<GraphVersionList>> GetVersionSupportedList()
{
	auto  list = std::make_shared<std::vector<GraphVersionList>>();
	list->push_back(GraphVersionList(toy::GL_2_0,"2.0"));
	return list;
}
#endif

static inline bool IsVersionOK( std::shared_ptr<std::vector<GraphVersionList>> list, enum toy::Option *expectVersion )
{
	auto    maximum = list->front().version;
	auto    minimum = list->back().version;
	auto    expect  = *expectVersion;

	if ( minimum<toy::GL_2_0 )
	{
		minimum = toy::GL_2_0;
	}

	if ( minimum==toy::NOTHING )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( expect<toy::GL_1_1 || expect>toy::GL_4_5 )
	{
		toy::Oops(TOY_MARK);
		*expectVersion = maximum;
		return true;
	}

	if ( expect<toy::GL_2_0 )
	{
		toy::Logger<<"Warning:ToyBox not support the version older than 2.0"<<toy::NewLine;
		*expectVersion = minimum;
		return true;
	}

	if ( minimum>expect )
	{
		toy::Logger<<"Warning:The OpenGL version you ask is too old to supported"<<toy::NewLine;
		*expectVersion = minimum;
		return true;
	}

	if ( maximum<expect )
	{
		toy::Logger<<"Error:The current OpenGL version is older than you want"<<toy::NewLine;
		*expectVersion = maximum;
		return true;
	}

	return true;
}

bool CheckVersion(enum toy::Option *expectVersion)
{
	const std::string   str("OpenGL version supported : ");

	toy::Logger<<str<<glGetString(GL_VERSION)<<R"( (got from "glGetString"))"<<toy::NewLine;

	#if TOY_OPTION_USE_GLEW
	GLenum	err = glewInit();

	if ( GLEW_OK != err )
	{
		toy::Logger<<"Error:glew initial failed"<<toy::NewLine;
		toy::Logger<<"Error:"<<glewGetErrorString(err)<<toy::NewLine;
		return false;
	}
	#endif

	auto   list = GetVersionSupportedList();

	#if TOY_OPTION_USE_GLEW
	toy::Logger<<str<<list->back().str<<"~"<<list->front().str<<" (got from GLEW)"<<toy::NewLine;
	#else
	toy::Logger<<str<<list->front().str<<" (assumed)"<<toy::NewLine;
	#endif

	if ( *expectVersion==toy::WHATEVER )
	{
		*expectVersion = list->front().version;
	}

	return IsVersionOK( list, expectVersion );
}

}}
