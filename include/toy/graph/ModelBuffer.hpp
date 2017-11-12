
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Export.hpp"
#include "toy/graph/VertexBuffer.hpp"

namespace toy{
namespace graph{
class Brush;
struct ModelBufferPrivate;

class TOY_API_GRAPH ModelBuffer
{
	public:

		ModelBuffer(std::shared_ptr<toy::graph::Brush>);
		~ModelBuffer();

		void setShape(const std::vector<toy::graph::VertexBuffer> &data);

		void setIndices(const std::vector<uint8_t> &data);
		void setIndices(const std::initializer_list<uint8_t> data);

	private:

		ModelBufferPrivate*     _this = nullptr;

	public:

		const void* _data() const;
};

}}
