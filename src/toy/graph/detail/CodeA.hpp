
#pragma once

#include "toy/graph/Standard.hpp"
#include "toy/graph/detail/Code.hpp"

namespace toy{
namespace graph{
namespace _detail{

class CodeA : public toy::graph::_detail::Code
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
