
#pragma once

#include "toy/graph/Standard.hpp"
#include "toy/graph/detail/Program.hpp"

namespace toy{
namespace graph{
namespace _detail{

/*
 * For OpenGL 3.0
 */
class ProgramA : public toy::graph::_detail::Program
{
	public:

		ProgramA( std::shared_ptr<toy::graph::Code> vs,
		          std::shared_ptr<toy::graph::Code> fs );

		~ProgramA();

		void use();
		auto getProgramID()->uint32_t;

	private:

		GLuint    _program = 0;
};


}}}
