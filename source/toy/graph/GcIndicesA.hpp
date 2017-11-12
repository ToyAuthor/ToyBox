
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace graph{

class Brush;

class GcIndicesA
{
	public:

		GcIndicesA(std::shared_ptr<toy::graph::Brush> ptr,const std::vector<uint8_t> &buffer);
		~GcIndicesA();

	private:

		std::shared_ptr<toy::graph::Brush>   _brush = nullptr;
		GLuint                               _handle = 0;

	public:

		void _bind();
};


}}
