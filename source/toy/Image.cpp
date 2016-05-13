#include <cstdlib>
#include <cstring>
#include "toy/Image.hpp"
#include "toy/Math.hpp"

using namespace toy;


Image::Image()
{
	;
}

Image::~Image()
{
	clean();
}

void Image::clean()
{
	_data.free();
}
