
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/VertexBuffer.hpp"

namespace toy{
namespace canvas{
namespace _detail{


class ModelBuffer
{
	public:

		ModelBuffer(){}
		virtual ~ModelBuffer(){}

		virtual void setShape(const std::vector<toy::canvas::VertexBuffer> &data)=0;
		virtual void setIndices(const std::vector<uint8_t> &data)=0;
		virtual void setIndices(const std::initializer_list<uint8_t> &data)=0;

		virtual const void* data() const=0;
};


}}}
