#include "toy/canvas/Code.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Factory.hpp"

namespace toy{
namespace canvas{
struct CodePrivate
{
	std::unique_ptr<toy::canvas::_detail::Code>   detail;
};
}}

using namespace toy;
using namespace canvas;

Code::Code(std::shared_ptr<Brush> brush,std::string filename, enum toy::Option type):
	_this(new CodePrivate),
	_brush(brush)
{
	_this->detail.reset(brush->_getFactory()->createCode_02(filename,type));
}

Code::Code(std::shared_ptr<Brush> brush,toy::Text &code, enum toy::Option type):
	_this(new CodePrivate),
	_brush(brush)
{
	_this->detail.reset(brush->_getFactory()->createCode_01(code,type));
}

Code::~Code()
{
	;
}

bool Code::isExist()
{
	return _this->detail->isExist();
}

auto Code::brush()->std::shared_ptr<Brush>
{
	return _brush;
}

void Code::drop()
{
	_this->detail->drop();
}

uint32_t Code::_getShaderID()
{
	return _this->detail->getShaderID();
}
