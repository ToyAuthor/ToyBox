
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace graph{
namespace _detail{

class Code
{
	public:

		Code(){}
		virtual ~Code(){}

		virtual bool isExist()=0;
		virtual void drop()=0;

		virtual auto getShaderID()->uint32_t=0;
};



}}}
