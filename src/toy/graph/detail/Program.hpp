
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace graph{
class Code;

namespace _detail{


class Program
{
	public:

		Program(){}

		virtual ~Program(){}

		virtual void use()=0;
		virtual auto getProgramID()->uint32_t=0;
};


}}}
