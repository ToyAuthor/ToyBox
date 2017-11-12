#include "toy/graph/Factory.hpp"
#include "toy/graph/detail/MakeUpFactory.hpp"

namespace toy{
namespace graph{

bool CreateFactory(enum toy::Option version,toy::graph::Factory **factory)
{
	return MakeUpFactory(version,factory);
}

}}
