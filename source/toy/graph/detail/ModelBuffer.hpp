
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/VertexBuffer.hpp"

namespace toy{
namespace graph{
namespace _detail{


class ModelBuffer
{
	public:

		ModelBuffer(){}
		virtual ~ModelBuffer(){}

		virtual void setShape(const std::vector<toy::graph::VertexBuffer> &data)=0;
		virtual void setIndices(const std::vector<uint8_t> &data)=0;
		virtual void setIndices(const std::initializer_list<uint8_t> &data)=0;

		virtual const void* data() const=0;
};


}}}
