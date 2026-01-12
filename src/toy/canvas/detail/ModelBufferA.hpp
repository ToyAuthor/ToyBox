
#pragma once

#include "toy/canvas/detail/ModelBuffer.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class ModelBufferA : public toy::canvas::_detail::ModelBuffer
{
	public:

		ModelBufferA();
		~ModelBufferA();

		void setShape(const std::vector<VertexBuffer> &data);
		void setIndices(const std::vector<uint8_t> &data);
		void setIndices(const std::initializer_list<uint8_t> &data);

		const void* data() const;

	private:

		struct DataPak
		{
			std::vector<float>     vertex;
			std::vector<uint8_t>   indices;
		};

		DataPak      _data;
};

}}}
