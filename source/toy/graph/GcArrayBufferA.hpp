
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Array.hpp"
#include "toy/graph/Standard.hpp"

namespace toy{
namespace graph{

class Brush;

// Buffer on graphics card.
class GcArrayBufferA
{
	public:

		GcArrayBufferA(std::shared_ptr<toy::graph::Brush> ptr,const std::vector<float> &buffer);
		GcArrayBufferA(std::shared_ptr<toy::graph::Brush> ptr,const toy::graph::Array3<float> &buffer);
		~GcArrayBufferA();

	private:

		std::shared_ptr<toy::graph::Brush>   _brush = nullptr;
		GLuint                               _handle = 0;

	public:

		void _bind();
};


}}
