
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Export.hpp"

namespace toy{
namespace graph{

struct VertexBufferPrivate;

class TOY_API_GRAPH VertexBuffer
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

		::toy::graph::VertexBufferPrivate*     _this = nullptr;

	public:

		const void* _data() const;
};

}}
