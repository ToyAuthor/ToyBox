#include "toy/graph/Standard.hpp"
#include "toy/graph/VertexBuffer.hpp"

namespace toy{
namespace graph{

struct VertexBufferPrivate
{
	float   data[8] = {0.0f};
};

}}

using namespace toy;
using namespace graph;

VertexBuffer::VertexBuffer():_this(new VertexBufferPrivate)
{
	;
}

VertexBuffer::VertexBuffer(const VertexBuffer &mykind):_this(new VertexBufferPrivate)
{
	*_this = *(mykind._this);
}

VertexBuffer::~VertexBuffer()
{
	delete _this;
}

const void* VertexBuffer::_data() const
{
	return static_cast<const void*>(_this->data);
}

bool VertexBuffer::good() const
{
	return true;
}

void VertexBuffer::setPosition(float x,float y,float z)
{
	_this->data[0] = x;
	_this->data[1] = y;
	_this->data[2] = z;
}

void VertexBuffer::setVector(float x,float y,float z)
{
	_this->data[3] = x;
	_this->data[4] = y;
	_this->data[5] = z;
}

void VertexBuffer::setTexture(float u,float v)
{
	_this->data[6] = u;
	_this->data[7] = v;
}

auto VertexBuffer::operator = (const VertexBuffer &mykind)->const VertexBuffer&
{
	*_this = *(mykind._this);
	return *this;
}
