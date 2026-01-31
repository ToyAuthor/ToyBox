
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

		Color(uint8_t v);
		Color(float   v);
		Color(uint8_t v,uint8_t a);
		Color(float   v,float   a);
		Color(uint8_t r,uint8_t g,uint8_t b);
		Color(float   r,float   g,float   b);
		Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a);
		Color(float   r,float   g,float   b,float   a);
		Color(const Color&);
		Color& operator = (const Color&);
		~Color();

		//-------------Grey scale-------------
		void set(uint8_t  v);
		void get(uint8_t* v) const;
		void set(float    v);
		void get(float*   v) const;

		//-------------Grey alpha-------------
		void set(uint8_t  v,uint8_t  a);
		void get(uint8_t* v,uint8_t* a) const;
		void set(float    v,float    a);
		void get(float*   v,float*   a) const;

		//-------------RGB-------------
		void set(uint8_t  r,uint8_t  g,uint8_t  b);
		void get(uint8_t* r,uint8_t* g,uint8_t* b) const;
		void set(float    r,float    g,float    b);
		void get(float*   r,float*   g,float*   b) const;

		//-------------RGBA-------------
		void set(uint8_t  r,uint8_t  g,uint8_t  b,uint8_t  a);
		void get(uint8_t* r,uint8_t* g,uint8_t* b,uint8_t* a) const;
		void set(float    r,float    g,float    b,float    a);
		void get(float*   r,float*   g,float*   b,float*   a) const;

		void grey(float);
		void grey(uint8_t);
		void red(float);
		void red(uint8_t);
		void green(float);
		void green(uint8_t);
		void blue(float);
		void blue(uint8_t);
		void alpha(float);
		void alpha(uint8_t);

		auto grey()   const -> ::toy::_PrimaryColor;
		auto red()   const -> ::toy::_PrimaryColor;
		auto green() const -> ::toy::_PrimaryColor;
		auto blue()  const -> ::toy::_PrimaryColor;
		auto alpha() const -> ::toy::_PrimaryColor;

	private:

		std::unique_ptr<ColorPrivate> _this;
};

}
