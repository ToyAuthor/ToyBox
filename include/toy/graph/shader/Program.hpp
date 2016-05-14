
#pragma once

#include "toy/graph/Standard.hpp"
#include "toy/graph/shader/Code.hpp"


namespace toy{
namespace graph{
namespace shader{



class TOY_API Program
{
	public:

		Program();
		~Program();

		int     loadShader( const char *fileVertex,
		                    const char *fileFragment
		                    );

		void    create();
		void    use();

		Code     _vertex;
		Code     _fragment;
		GLuint   _program = 0;
};



}//namespace shader{
}//namespace graph{
}//namespace toy{
