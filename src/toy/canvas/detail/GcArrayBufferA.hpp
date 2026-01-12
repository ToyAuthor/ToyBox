
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Array.hpp"
#include "toy/canvas/Standard.hpp"

namespace toy{
namespace canvas{
class Brush;
namespace _detail{

// Buffer on graphics card.
class GcArrayBufferA
{
	public:

		GcArrayBufferA(std::shared_ptr<toy::canvas::Brush> ptr,const std::vector<float> &buffer);
		GcArrayBufferA(std::shared_ptr<toy::canvas::Brush> ptr,const toy::canvas::Array3<float> &buffer);
		~GcArrayBufferA();

		void setPosition(const float* data);

	private:

		std::shared_ptr<toy::canvas::Brush>  _brush = nullptr;
		GLuint                               _handle = 0;

	public:

		void _bind();
};

}}}
