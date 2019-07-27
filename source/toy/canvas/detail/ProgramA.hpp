
#pragma once

#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/Program.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class ProgramA : public toy::canvas::_detail::Program
{
	public:

		ProgramA( std::shared_ptr<toy::canvas::Code> vs,
		          std::shared_ptr<toy::canvas::Code> fs );

		~ProgramA();

		void use();
		auto getProgramID()->uint32_t;

	private:

		GLuint    _program = 0;
};

}}}
