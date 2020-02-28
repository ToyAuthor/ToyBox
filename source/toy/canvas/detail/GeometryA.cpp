#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Program.hpp"
#include "toy/canvas/detail/GcArrayBufferA.hpp"
#include "toy/canvas/detail/GeometryA.hpp"

static inline std::string GetVertexShaderCode()
{
	#if defined(TOY_LINUX)
		// Ubuntu need this to use VertexAttribPointer.
		std::string    top = "#version 130";
	#else
		std::string    top = "// nothing";
	#endif

	return top + R"(
		void main(void)
		{
			gl_Position = ftransform();
		}
	)";
}

static inline std::string GetFragmentShaderCode()
{
	return R"(
		void main(void)
		{
			gl_FragColor = vec4(1,0,0,0);
		}
	)";
}

static inline auto BuildDefaultProgram(std::shared_ptr<toy::canvas::Brush> brush)
->std::shared_ptr<toy::canvas::Program>
{
	toy::Text  text1(GetVertexShaderCode());

	auto   vs = std::make_shared<toy::canvas::Code>(brush,text1,toy::VERTEX_SHADER);

	toy::Text  text2(GetFragmentShaderCode());

	auto   fs = std::make_shared<toy::canvas::Code>(brush,text2,toy::FRAGMENT_SHADER);

	return std::make_shared<toy::canvas::Program>(vs,fs);
}

static inline auto InitCommonProgram(std::shared_ptr<::toy::canvas::Brush> brush)
->std::shared_ptr<toy::canvas::Program>
{
	static std::weak_ptr<::toy::canvas::Program>   program;

	if ( program.expired() )
	{
		auto  ptr = BuildDefaultProgram(brush);
		program = ptr;
		return ptr;
	}
	else
	{
		return program.lock();
	}
}

using namespace toy;
using namespace canvas;
using namespace _detail;

GeometryA::GeometryA(std::shared_ptr<toy::canvas::Brush> brush)
{
	this->setProgram(InitCommonProgram(brush));
}

GeometryA::~GeometryA()
{
	;
}

void GeometryA::visible(bool show)
{
	_isVisible = show;
}

bool GeometryA::isVisible() const
{
	return _isVisible;
}

void GeometryA::setModel(std::shared_ptr<toy::canvas::Brush> brush,toy::canvas::Array3<float> data)
{
	_vList = std::make_shared<toy::canvas::_detail::GcArrayBufferA>(brush,data);
}

void GeometryA::setProgram(std::shared_ptr<toy::canvas::Program> program)
{
	_program = program;
}

auto GeometryA::getProgram()->std::shared_ptr<toy::canvas::Program>
{
	return _program;
}

void GeometryA::bind(std::shared_ptr<toy::canvas::Brush> brush)
{
	if ( _program )
	{
		_program->use();
	}
	else
	{
		brush->_useProgram(nullptr);
	}

	_vList->_bind();
}

void GeometryA::render()
{
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
