#include "toy/graph/Brush.hpp"
#include "toy/graph/GcArrayBufferA.hpp"
#include "toy/graph/detail/GeometryA.hpp"

using namespace toy;
using namespace graph;
using namespace _detail;


GeometryA::GeometryA()
{
	;
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

void GeometryA::setModel(std::shared_ptr<toy::graph::Brush> brush,toy::graph::Array3<float> data)
{
	_vList = std::make_shared<toy::graph::GcArrayBufferA>(brush,data);
}

void GeometryA::setProgram(std::shared_ptr<toy::graph::Program> program)
{
	_program = program;
}

auto GeometryA::getProgram()->std::shared_ptr<toy::graph::Program>
{
	return _program;
}

void GeometryA::bind(std::shared_ptr<toy::graph::Brush> brush)
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
