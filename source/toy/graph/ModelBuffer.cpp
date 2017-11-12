#include "toy/graph/Standard.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/ModelBuffer.hpp"
#include "toy/graph/Factory.hpp"

namespace toy{
namespace graph{

struct ModelBufferPrivate
{
	toy::graph::_detail::ModelBuffer*   detail = nullptr;
};

}}


using namespace toy;
using namespace graph;


ModelBuffer::ModelBuffer(std::shared_ptr<toy::graph::Brush> brush):_this(new ModelBufferPrivate)
{
	_this->detail = brush->_getFactory()->createModelBuffer();
}

ModelBuffer::~ModelBuffer()
{
	delete _this->detail;
	delete _this;
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
