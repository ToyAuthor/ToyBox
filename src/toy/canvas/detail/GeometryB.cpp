#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Program.hpp"
#include "toy/canvas/detail/GcArrayBufferA.hpp"
#include "toy/canvas/detail/GeometryB.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;


GeometryB::GeometryB(std::shared_ptr<toy::canvas::Brush>)
{
	;
}

GeometryB::~GeometryB()
{
	;
}

void GeometryB::visible(bool show)
{
	_isVisible = show;
}

bool GeometryB::isVisible() const
{
	return _isVisible;
}

void GeometryB::setModel(std::shared_ptr<toy::canvas::Brush> brush,toy::canvas::Array3<float> data)
{
	_vList = std::make_shared<toy::canvas::_detail::GcArrayBufferA>(brush,data);
}

void GeometryB::setProgram(std::shared_ptr<toy::canvas::Program> program)
{
	_program = program;
}

auto GeometryB::getProgram()->std::shared_ptr<toy::canvas::Program>
{
	return _program;
}

void GeometryB::bind(std::shared_ptr<toy::canvas::Brush> brush)
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

void GeometryB::render()
{
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
