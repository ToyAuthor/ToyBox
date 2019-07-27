
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace canvas{
class Brush;
namespace _detail{

class GcIndicesA
{
	public:

		GcIndicesA(std::shared_ptr<toy::canvas::Brush> ptr,const std::vector<uint8_t> &buffer);
		~GcIndicesA();

	private:

		std::shared_ptr<toy::canvas::Brush>  _brush = nullptr;
		GLuint                               _handle = 0;

	public:

		void _bind();
};

}}}
