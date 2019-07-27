
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Export.hpp"
#include "toy/canvas/VertexBuffer.hpp"

namespace toy{
namespace canvas{
class Brush;
struct ModelBufferPrivate;

class TOY_API_CANVAS ModelBuffer
{
	public:

		ModelBuffer(std::shared_ptr<toy::canvas::Brush>);
		~ModelBuffer();

		void setShape(const std::vector<toy::canvas::VertexBuffer> &data);

		void setIndices(const std::vector<uint8_t> &data);
		void setIndices(const std::initializer_list<uint8_t> data);

	private:

		std::unique_ptr<ModelBufferPrivate>    _this;

	public:

		const void* _data() const;
};

}}
