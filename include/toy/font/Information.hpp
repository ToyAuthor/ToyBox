
#pragma once

namespace toy{
namespace font{

// See ToyBox/doc/extlibs/freetype/metrics.png
struct Metrics
{
	float    width        = 0;
	float    height       = 0;
	float    horiBearingX = 0;
	float    horiBearingY = 0;
	float    horiAdvance  = 0;
	float    vertBearingX = 0;
	float    vertBearingY = 0;
	float    vertAdvance  = 0;
};

struct Information
{
	struct Metrics    metrics;
};

}}
