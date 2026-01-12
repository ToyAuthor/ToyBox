
#include "toy/canvas/Standard.hpp"
#include "toy/canvas/CheckVersion.hpp"
#include "toy/canvas/MakeUpFactory.hpp"

//------------------------------------------------------------------------------

#include "toy/canvas/detail/BrushA.hpp"
#include "toy/canvas/detail/BrushB.hpp"
#include "toy/canvas/detail/CodeA.hpp"
#include "toy/canvas/detail/ProgramA.hpp"
#include "toy/canvas/detail/ModelBufferA.hpp"
#include "toy/canvas/detail/ImageA.hpp"
#include "toy/canvas/detail/ImageB.hpp"
#include "toy/canvas/detail/GeometryA.hpp"
#include "toy/canvas/detail/GeometryB.hpp"
#include "toy/canvas/detail/CanvasA.hpp"

//------------------------------------------------------------------------------

static auto CreateBrushA()->toy::canvas::_detail::Brush*
{
	return new toy::canvas::_detail::BrushA;
}

static auto CreateBrushB()->toy::canvas::_detail::Brush*
{
	return new toy::canvas::_detail::BrushB;
}

static auto CreateCodeA_01(toy::Text &code, enum toy::Option type)->toy::canvas::_detail::Code*
{
	return new toy::canvas::_detail::CodeA(code,type);
}

static auto CreateCodeA_02(std::string filename, enum toy::Option type)->toy::canvas::_detail::Code*
{
	return new toy::canvas::_detail::CodeA(filename,type);
}

static auto CreateProgramA(std::shared_ptr<toy::canvas::Code> vs,std::shared_ptr<toy::canvas::Code> fs)->toy::canvas::_detail::Program*
{
	return new toy::canvas::_detail::ProgramA(vs,fs);
}

static auto CreateModelBufferA()->toy::canvas::_detail::ModelBuffer*
{
	return new toy::canvas::_detail::ModelBufferA;
}

static auto CreateImageA(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Image*
{
	return new toy::canvas::_detail::ImageA(brush);
}

static auto CreateImageB(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Image*
{
	return new toy::canvas::_detail::ImageB(brush);
}

static auto CreateGeometryA(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Geometry*
{
	return new toy::canvas::_detail::GeometryA(brush);
}

static auto CreateGeometryB(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Geometry*
{
	return new toy::canvas::_detail::GeometryB(brush);
}

static auto CreateCanvasA()->toy::canvas::_detail::Canvas*
{
	return new toy::canvas::_detail::CanvasA;
}

//------------------------------------------------------------------------------

namespace toy{
namespace canvas{

static std::string VersionToString(enum toy::Option version)
{
	switch (static_cast<int>(version))
	{
		case toy::GL_4_5: return "4.5";
		case toy::GL_4_4: return "4.4";
		case toy::GL_4_3: return "4.3";
		case toy::GL_4_2: return "4.2";
		case toy::GL_4_1: return "4.1";
		case toy::GL_4_0: return "4.0";
		case toy::GL_3_3: return "3.3";
		case toy::GL_3_2: return "3.2";
		case toy::GL_3_1: return "3.1";
		case toy::GL_3_0: return "3.0";
		case toy::GL_2_1: return "2.1";
		case toy::GL_2_0: return "2.0";
		case toy::GL_1_5: return "1.5";
		case toy::GL_1_4: return "1.4";
		case toy::GL_1_3: return "1.3";
		case toy::GL_1_2: return "1.2";
		case toy::GL_1_1: return "1.1";
	}

	return "none";
}

bool MakeUpFactory(enum toy::Option version,toy::canvas::Factory **factory_address)
{
	if ( ! toy::canvas::CheckVersion(&version) )
	{
		*factory_address = nullptr;
		return false;
	}

	toy::Logger<<"Actually OpenGL version used : "<<VersionToString(version)<<toy::NewLine;

	toy::canvas::Factory::Config config;

	//--------------------------------------------------------------------------

	if ( version >= toy::GL_3_0 )
	{
		config.createBrush = CreateBrushA;
		config.createCode_01 = CreateCodeA_01;
		config.createCode_02 = CreateCodeA_02;
		config.createProgram = CreateProgramA;
		config.createModelBuffer = CreateModelBufferA;
		config.createImage = CreateImageA;
		config.createGeometry = CreateGeometryA;
		config.createCanvas = CreateCanvasA;
	}
	else if ( version >= toy::GL_2_0 )
	{
		config.createBrush = CreateBrushB;
		config.createCode_01 = CreateCodeA_01;
		config.createCode_02 = CreateCodeA_02;
		config.createProgram = CreateProgramA;
		config.createModelBuffer = CreateModelBufferA;
		config.createImage = CreateImageB;
		config.createGeometry = CreateGeometryB;
		config.createCanvas = CreateCanvasA;
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	//--------------------------------------------------------------------------

	*factory_address = new toy::canvas::Factory(config);

	return true;
}

}}
