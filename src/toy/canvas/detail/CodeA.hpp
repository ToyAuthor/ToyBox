
#pragma once

#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/Code.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class CodeA : public toy::canvas::_detail::Code
{
	public:

		CodeA(std::string filename, enum toy::Option type);
		CodeA(toy::Text &code, enum toy::Option type);
		~CodeA();

		bool isExist();
		void drop();
		uint32_t getShaderID();

	private:

		GLuint    _shaderID = 0;
};



}}}
