
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Export.hpp"

namespace toy{
namespace canvas{

struct VertexBufferPrivate;

class TOY_API_CANVAS VertexBuffer
{
	public:

		VertexBuffer(const VertexBuffer &);
		VertexBuffer();
		~VertexBuffer();

		void setPosition(float x,float y,float z);
		void setVector(float x,float y,float z);   // Normal vector
		void setTexture(float u,float v);          // Texture coord

		auto operator = (const VertexBuffer &)->const VertexBuffer &;

		bool good() const;

	private:

		std::unique_ptr<::toy::canvas::VertexBufferPrivate>     _this;

	public:

		const void* _data() const;
};

}}
