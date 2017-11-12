#include "toy/graph/detail/ModelBufferA.hpp"


using namespace toy;
using namespace graph;
using namespace _detail;


ModelBufferA::ModelBufferA()
{
	;
}

ModelBufferA::~ModelBufferA()
{
	;
}


void ModelBufferA::setShape(const std::vector<VertexBuffer> &data)
{
	//_data.vertex.clear();

	for ( auto &item : data )
	{
		auto  array = static_cast<const float*>(item._data());

		_data.vertex.push_back(array[0]);
		_data.vertex.push_back(array[1]);
		_data.vertex.push_back(array[2]);
		_data.vertex.push_back(array[3]);
		_data.vertex.push_back(array[4]);
		_data.vertex.push_back(array[5]);
		_data.vertex.push_back(array[6]);
		_data.vertex.push_back(array[7]);
	}
}

void ModelBufferA::setIndices(const std::vector<uint8_t> &data)
{
	_data.indices = data;
}

void ModelBufferA::setIndices(const std::initializer_list<uint8_t> &data)
{
	_data.indices.insert(_data.indices.end(), data.begin(), data.end());
}

const void* ModelBufferA::data() const
{
	return static_cast<const void*>(&_data);
}
