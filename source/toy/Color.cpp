#include "toy/Color.hpp"

namespace toy{

struct ColorPrivate
{
	float r = float(0);
	float g = float(0);
	float b = float(0);
	float a = float(0);
};

static inline float IntToFloat(uint8_t num)
{
	return static_cast<float>(num) / float(255);
}

static inline uint8_t FloatToInt(float num)
{
	if ( num>float(1) )
	{
		num = float(1);
	}

	num *= float(255);
	num += float(0.5);

	return static_cast<uint8_t>(num);
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

Color::Color(const Color& bro):_this(new ::toy::ColorPrivate)
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

void Color::red(float     color) { _this->r = color; }
void Color::red(uint8_t   color) { _this->r = IntToFloat(color); }
void Color::green(float   color) { _this->g = color; }
void Color::green(uint8_t color) { _this->g = IntToFloat(color); }
void Color::blue(float    color) { _this->b = color; }
void Color::blue(uint8_t  color) { _this->b = IntToFloat(color); }
void Color::alpha(float   color) { _this->a = color; }
void Color::alpha(uint8_t color) { _this->a = IntToFloat(color); }

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
