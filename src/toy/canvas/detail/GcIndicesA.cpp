#include "toy/Exception.hpp"
#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/GcIndicesA.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

GcIndicesA::GcIndicesA(std::shared_ptr<toy::canvas::Brush> ptr,const std::vector<uint8_t> &buffer):_brush(ptr)
{
	glGenBuffers(1, &(_handle));

	if ( _handle==0 )
	{
		throw toy::Exception(TOY_MARK);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8_t)*buffer.size(), buffer.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GcIndicesA::~GcIndicesA()
{
	glDeleteBuffers(1, &(_handle));
}

void GcIndicesA::_bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
}
