#include "toy/graph/Code.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/Factory.hpp"

namespace toy{
namespace graph{
struct CodePrivate
{
	std::unique_ptr<toy::graph::_detail::Code>   detail;
};
}}

using namespace toy;
using namespace graph;

Code::Code(std::shared_ptr<Brush> brush,std::string filename, enum toy::Option type):
	_this(new CodePrivate),
	_brush(brush)
{
	_this->detail.reset(brush->_getFactory()->createCode02(filename,type));
}

Code::Code(std::shared_ptr<Brush> brush,toy::Text &code, enum toy::Option type):
	_this(new CodePrivate),
	_brush(brush)
{
	_this->detail.reset(brush->_getFactory()->createCode01(code,type));
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
