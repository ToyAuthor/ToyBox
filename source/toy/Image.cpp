#include <cstdlib>
#include <cstring>
#include "toy/Image.hpp"
#include "toy/Math.hpp"

using namespace toy;

using math::exp1;

Image::Image()
{
	;
}

Image::~Image()
{
	Clean();
}

void Image::Clean()
{
	mData.Free();
}
