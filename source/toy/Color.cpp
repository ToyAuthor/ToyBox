#include "toy/Color.hpp"

namespace toy{

struct ColorPrivate
{
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
};

inline static float IntToFloat(uint8_t num)
{
	return ((float)num) / 255.0f;
}

inline static uint8_t FloatToInt(float num)
{
	if ( num>1.0f )
	{
		num = 1.0f;
	}

	num *= 255.0f;
	num += 0.5f;

	return (uint8_t)num;
}

}

using namespace toy;

_PrimaryColor::_PrimaryColor(float cc):_color(cc)
{
	;
}

_PrimaryColor::~_PrimaryColor()
{
	;
}

_PrimaryColor::operator float()
{
	return _color;
}

_PrimaryColor::operator uint8_t()
{
	return FloatToInt(_color);
}

Color::Color(const Color& bro)
{
	*_this = *(bro._this);
}

Color& Color::operator = (const Color& bro)
{
	*_this = *(bro._this);
	return *this;
}

Color::Color():_this(new ::toy::ColorPrivate)
{
	;
}

Color::Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a):_this(new ::toy::ColorPrivate)
{
	_this->r = IntToFloat(r);
	_this->g = IntToFloat(g);
	_this->b = IntToFloat(b);
	_this->a = IntToFloat(a);
}

Color::Color(float r,float g,float b,float a):_this(new ::toy::ColorPrivate)
{
	_this->r = r;
	_this->g = g;
	_this->b = b;
	_this->a = a;
}

Color::~Color()
{
	delete _this;
}

void Color::data(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
	_this->r = IntToFloat(r);
	_this->g = IntToFloat(g);
	_this->b = IntToFloat(b);
	_this->a = IntToFloat(a);
}

void Color::data(uint8_t *r,uint8_t *g,uint8_t *b,uint8_t *a) const
{
	*r = FloatToInt(_this->r);
	*g = FloatToInt(_this->g);
	*b = FloatToInt(_this->b);
	*a = FloatToInt(_this->a);
}

void Color::data(float r,float g,float b,float a)
{
	_this->r = r;
	_this->g = g;
	_this->b = b;
	_this->a = a;
}

void Color::data(float *r,float *g,float *b,float *a) const
{
	*r = _this->r;
	*g = _this->g;
	*b = _this->b;
	*a = _this->a;
}

auto Color::red() const->_PrimaryColor
{
	return _PrimaryColor(_this->r);
}

auto Color::green() const->_PrimaryColor
{
	return _PrimaryColor(_this->g);
}

auto Color::blue() const->_PrimaryColor
{
	return _PrimaryColor(_this->b);
}

auto Color::alpha() const->_PrimaryColor
{
	return _PrimaryColor(_this->a);
}
