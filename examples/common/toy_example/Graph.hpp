
#pragma once

#include <toy/Graph.hpp>

namespace toy{
namespace example{

inline static auto CreateBrush( enum toy::Option option = toy::WHATEVER)
->std::shared_ptr<toy::graph::Brush>
{
	bool result = false;

	auto ptr = std::make_shared<toy::graph::Brush>(option,&result);

	if ( result )
	{
		return ptr;
	}

	return nullptr;
}

}}
