#include "toy/Ooops.hpp"
#include "toy/math/SafeInt.hpp"
#include "toy/photo/Tools.hpp"

namespace toy{
namespace photo{

static void Resize_RGBA_EditDownwardOnly(toy::ImageBuffer *image,int32_t downward,const toy::Color &color)
{
	auto allocator = image->_getAllocator();
	auto height    = image->height();
	auto size      = allocator->size();

	if ( downward==0 ) return;

	if ( downward<0 )
	{
		auto downwardTag = toy::math::SafeInt<decltype(height)>(downward*-1,TOY_MARK);

		if ( image->height() <= downwardTag )
		{
			toy::Oops(TOY_MARK);

			downwardTag -= 1;
		}

		height -= downwardTag;

		allocator->size(toy::math::SafeInt<decltype(size)>(image->width()*height*4,TOY_MARK) );

		image->_setHeight(height);

		return;
	}

	if ( downward>0 )
	{
		height += toy::math::SafeInt<decltype(height)>(downward,TOY_MARK);

		allocator->size(toy::math::SafeInt<decltype(size)>(image->width()*height*4,TOY_MARK) );
		image->_setHeight(height);

		auto ptr = image->_data();

		ptr += (size-1*4);

		for ( ; downward>0 ; downward-- )
		{
			ptr += 4;
			color.data(ptr,ptr+1,ptr+2,ptr+3);
		}

		return;
	}
}

static void Resize_RGBA_MoveFromHead(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward,const toy::Color &color)
{
	(void)image;
	(void)topward;
	(void)downward;
	(void)leftward;
	(void)rightward;
	(void)color;
	toy::Oops(TOY_MARK);
}

static void Resize_RGBA_MoveFromBack(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward,const toy::Color &color)
{
	(void)image;
	(void)topward;
	(void)downward;
	(void)leftward;
	(void)rightward;
	(void)color;
	toy::Oops(TOY_MARK);
}

static void Resize_RGBA_EntireCopy(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward,const toy::Color &color)
{
	(void)image;
	(void)topward;
	(void)downward;
	(void)leftward;
	(void)rightward;
	(void)color;
	toy::Oops(TOY_MARK);
}

static void Resize_RGBA(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward,const toy::Color &color)
{
	if ( topward==0 && leftward==0 && rightward==0 )
	{
		Resize_RGBA_EditDownwardOnly(image,downward,color);
		return;
	}

	auto height    = image->height();

	if ( (topward+downward)<0 )
	{
		if ( toy::math::SafeInt<decltype(height)>((topward+downward)*-1,TOY_MARK)>=height )
		{
			toy::Ooops(TOY_MARK);
			return;
		}
	}

	auto leftAndRight = leftward+rightward;

	if ( leftAndRight<0 )
	{
		if ( toy::math::SafeInt<decltype(height)>(leftAndRight*-1,TOY_MARK)>=image->width() )
		{
			toy::Ooops(TOY_MARK);
			return;
		}
	}

	if ( leftAndRight>0 )
	{
		Resize_RGBA_EntireCopy(image, topward, downward, leftward, rightward, color);
		return;
	}
	if ( leftAndRight==0 )
	{
		if ( topward>0 )
		{
			Resize_RGBA_MoveFromBack(image, topward, downward, leftward, rightward, color);
			return;
		}
		else
		{
			Resize_RGBA_MoveFromHead(image, topward, downward, leftward, rightward, color);
			return;
		}
	}
	else
	{
		if ( topward>0 )
		{
			Resize_RGBA_EntireCopy(image, topward, downward, leftward, rightward, color);
			return;
		}
		else
		{
			Resize_RGBA_MoveFromHead(image, topward, downward, leftward, rightward, color);
			return;
		}
	}
}

void Resize(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward)
{
	if ( image->empty() ) throw toy::Exception(TOY_MARK);

	if ( image->format()==toy::RGBA )
	{
		Resize_RGBA(image,topward,downward,leftward,rightward,toy::Color(float(0.0),float(0.0),float(0.0),float(0.0)));
	}
	else
	{
		throw toy::Exception(TOY_MARK);
	}
}

}}
