
#include "toy/graph/Standard.hpp"
#include "toy/graph/detail/MakeUpFactory.hpp"

//------------------------------------------------------------------------------

#include "toy/graph/detail/BrushA.hpp"
#include "toy/graph/detail/BrushB.hpp"
#include "toy/graph/detail/CodeA.hpp"
#include "toy/graph/detail/ProgramA.hpp"
#include "toy/graph/detail/ModelBufferA.hpp"
#include "toy/graph/detail/ImageA.hpp"
#include "toy/graph/detail/GeometryA.hpp"

//------------------------------------------------------------------------------

struct GraphVersionList
{
	GraphVersionList(enum toy::Option ver,std::string verstr):version(ver),str(verstr){}
	GraphVersionList(){}

	enum toy::Option  version = toy::NOTHING;
	std::string       str     = "Unknown";
};

#if TOY_OPTION_USE_GLEW
inline static std::vector<GraphVersionList> GetVersionSupportedList()
{
	std::vector<GraphVersionList>   list;

	if( GLEW_VERSION_4_5 )
	{
		list.push_back(GraphVersionList(toy::GL_4_5,"4.5"));
	}

	if( GLEW_VERSION_4_4 )
	{
		list.push_back(GraphVersionList(toy::GL_4_4,"4.4"));
	}

	if( GLEW_VERSION_4_3 )
	{
		list.push_back(GraphVersionList(toy::GL_4_3,"4.3"));
	}

	if( GLEW_VERSION_4_2 )
	{
		list.push_back(GraphVersionList(toy::GL_4_2,"4.2"));
	}

	if( GLEW_VERSION_4_1 )
	{
		list.push_back(GraphVersionList(toy::GL_4_1,"4.1"));
	}

	if( GLEW_VERSION_4_0 )
	{
		list.push_back(GraphVersionList(toy::GL_4_0,"4.0"));
	}

	if( GLEW_VERSION_3_3 )
	{
		list.push_back(GraphVersionList(toy::GL_3_3,"3.3"));
	}

	if( GLEW_VERSION_3_2 )
	{
		list.push_back(GraphVersionList(toy::GL_3_2,"3.2"));
	}

	if( GLEW_VERSION_3_1 )
	{
		list.push_back(GraphVersionList(toy::GL_3_1,"3.1"));
	}

	if( GLEW_VERSION_3_0 )
	{
		list.push_back(GraphVersionList(toy::GL_3_0,"3.0"));
	}

	if( GLEW_VERSION_2_1 )
	{
		list.push_back(GraphVersionList(toy::GL_2_1,"2.1"));
	}

	if( GLEW_VERSION_2_0 )
	{
		list.push_back(GraphVersionList(toy::GL_2_0,"2.0"));
	}

	if( GLEW_VERSION_1_5 )
	{
		list.push_back(GraphVersionList(toy::GL_1_5,"1.5"));
	}

	if( GLEW_VERSION_1_4 )
	{
		list.push_back(GraphVersionList(toy::GL_1_4,"1.4"));
	}

	if( GLEW_VERSION_1_3 )
	{
		list.push_back(GraphVersionList(toy::GL_1_3,"1.3"));
	}

	if( GLEW_VERSION_1_2 )
	{
		list.push_back(GraphVersionList(toy::GL_1_2,"1.2"));
	}

	if( GLEW_VERSION_1_1 )
	{
		list.push_back(GraphVersionList(toy::GL_1_1,"1.1"));
	}

	if ( list.empty() )
	{
		list.push_back(GraphVersionList());
	}

	return list;
}
#else
inline static std::vector<GraphVersionList> GetVersionSupportedList()
{
	std::vector<GraphVersionList>   list;
	list.push_back(GraphVersionList(toy::GL_2_0,"2.0"));
	return list;
}
#endif

inline static bool IsVersionOK( enum toy::Option maximum,
                                enum toy::Option minimum,
                                enum toy::Option expect )
{
	if ( minimum==toy::NOTHING )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( expect<toy::GL_1_1 || expect>toy::GL_4_5 )
	{
		toy::Logger<<"error:toy::graph::Brush::checkVersion() got a wrong parameter"<<toy::NextLine;
		return false;
	}

	if ( minimum>expect )
	{
		toy::Logger<<"error:The OpenGL version doesn't exist!"<<toy::NextLine;
		return false;
	}

	if ( maximum<expect )
	{
		toy::Logger<<"error:The OpenGL version is older than you want"<<toy::NextLine;
		return false;
	}

	return true;
}

inline static bool CheckVersion(enum toy::Option *expectVersion)
{
	const std::string   str("OpenGL version supported : ");

	toy::Logger<<str<<glGetString(GL_VERSION)<<R"( (got from "glGetString"))"<<toy::NextLine;

	#if TOY_OPTION_USE_GLEW
	GLenum	err = glewInit();

	if ( GLEW_OK != err )
	{
		toy::Logger<<"error:glew initial failed"<<toy::NextLine;
		toy::Logger<<"error:"<<glewGetErrorString(err)<<toy::NextLine;
		return false;
	}
	#endif

	auto   list = GetVersionSupportedList();

	#if TOY_OPTION_USE_GLEW
	toy::Logger<<str<<list.front().str<<" (got from GLEW)"<<toy::NextLine;
	#else
	toy::Logger<<str<<list.front().str<<" (assumed)"<<toy::NextLine;
	#endif

	if ( *expectVersion==toy::WHATEVER )
	{
		*expectVersion = list.front().version;
	}

	return IsVersionOK( list.front().version,
	                    list.back().version,
	                    *expectVersion );
}

//------------------------------------------------------------------------------

static auto CreateBrushA()->toy::graph::_detail::Brush*
{
	return new toy::graph::_detail::BrushA;
}

static auto CreateBrushB()->toy::graph::_detail::Brush*
{
	return new toy::graph::_detail::BrushB;
}

static auto CreateCodeA01(toy::Text &code, enum toy::Option type)->toy::graph::_detail::Code*
{
	return new toy::graph::_detail::CodeA(code,type);
}

static auto CreateCodeA02(std::string filename, enum toy::Option type)->toy::graph::_detail::Code*
{
	return new toy::graph::_detail::CodeA(filename,type);
}

static auto CreateProgramA(std::shared_ptr<toy::graph::Code> vs,std::shared_ptr<toy::graph::Code> fs)->toy::graph::_detail::Program*
{
	return new toy::graph::_detail::ProgramA(vs,fs);
}

static auto CreateModelBufferA()->toy::graph::_detail::ModelBuffer*
{
	return new toy::graph::_detail::ModelBufferA;
}

static auto CreateImageA(std::shared_ptr<::toy::graph::Brush> brush)->toy::graph::_detail::Image*
{
	return new toy::graph::_detail::ImageA(brush);
}

static auto CreateGeometryA()->toy::graph::_detail::Geometry*
{
	return new toy::graph::_detail::GeometryA;
}

//------------------------------------------------------------------------------

namespace toy{
namespace graph{

bool MakeUpFactory(enum toy::Option version,toy::graph::Factory **factory_address)
{
	if ( ! CheckVersion(&version) )
	{
		*factory_address = nullptr;
		return false;
	}

	toy::graph::Factory::Config config;

	//--------------------------------------------------------------------------

	if ( version >= toy::GL_3_0 )
	{
		config.createBrush = CreateBrushA;
		config.createCode01 = CreateCodeA01;
		config.createCode02 = CreateCodeA02;
		config.createProgram = CreateProgramA;
		config.createModelBuffer = CreateModelBufferA;
		config.createImage = CreateImageA;
		config.createGeometry = CreateGeometryA;
	}
	else if ( version >= toy::GL_2_0 )
	{
		config.createBrush = CreateBrushB;
		config.createCode01 = CreateCodeA01;
		config.createCode02 = CreateCodeA02;
		config.createProgram = CreateProgramA;
		config.createModelBuffer = CreateModelBufferA;
		config.createImage = CreateImageA;
		config.createGeometry = CreateGeometryA;
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	//--------------------------------------------------------------------------

	*factory_address = new toy::graph::Factory(config);

	return true;
}

}}
