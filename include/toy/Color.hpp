
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class TOY_API _PrimaryColor
{
	public:

		_PrimaryColor(float);
		~_PrimaryColor();

		operator float();
		operator uint8_t();

	private:

		float  _color;
};

struct ColorPrivate;

/*
 * float   : {0.0~1.0}
 * uint8_t : {0~255}
 */
class TOY_API Color
{
	public:

		Color();
		Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a);
		Color(float   r,float   g,float   b,float   a);
		Color(const Color&);
		Color& operator = (const Color&);
		~Color();

		void data(uint8_t  r,uint8_t  g,uint8_t  b,uint8_t  a);
		void data(uint8_t* r,uint8_t* g,uint8_t* b,uint8_t* a) const;
		void data(float    r,float    g,float    b,float    a);
		void data(float*   r,float*   g,float*   b,float*   a) const;

		auto red()   const->::toy::_PrimaryColor;
		auto green() const->::toy::_PrimaryColor;
		auto blue()  const->::toy::_PrimaryColor;
		auto alpha() const->::toy::_PrimaryColor;

	private:

		struct ColorPrivate* _this;
};

}
