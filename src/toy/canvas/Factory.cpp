#include "toy/canvas/Factory.hpp"
#include "toy/canvas/MakeUpFactory.hpp"

namespace toy{
namespace canvas{

bool CreateFactory(enum toy::Option version,toy::canvas::Factory **factory)
{
	return MakeUpFactory(version,factory);
}

}}
