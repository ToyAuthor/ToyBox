
#pragma once

#include "toy/graph/Standard.hpp"

namespace toy{
namespace graph{
namespace shader{



class TOY_API Code
{
	public:

		Code();
		~Code();

		void    drop();
		int     isExist();
		int     loadShader(std::string filename, GLenum type);

		GLuint  _shader = 0;
};



}//namespace shader{
}//namespace graph{
}//namespace toy{
