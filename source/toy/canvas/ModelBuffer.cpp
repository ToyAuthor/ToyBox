#include "toy/canvas/Standard.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/ModelBuffer.hpp"
#include "toy/canvas/Factory.hpp"

namespace toy{
namespace canvas{

struct ModelBufferPrivate
{
	std::unique_ptr<toy::canvas::_detail::ModelBuffer>   detail;
};

}}

using namespace toy;
using namespace canvas;

ModelBuffer::ModelBuffer(std::shared_ptr<toy::canvas::Brush> brush):_this(new ModelBufferPrivate)
{
	_this->detail.reset(brush->_getFactory()->createModelBuffer());
}

ModelBuffer::~ModelBuffer()
{
	;
}

const void* ModelBuffer::_data() const
{
	return _this->detail->data();
}

void ModelBuffer::setShape(const std::vector<VertexBuffer> &data)
{
	_this->detail->setShape(data);
}

void ModelBuffer::setIndices(const std::vector<uint8_t> &data)
{
	_this->detail->setIndices(data);
}

void ModelBuffer::setIndices(const std::initializer_list<uint8_t> data)
{
	_this->detail->setIndices(data);
}
