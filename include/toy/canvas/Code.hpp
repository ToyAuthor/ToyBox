
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Export.hpp"

namespace toy{
namespace canvas{
class  Brush;
struct CodePrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::canvas::Brush>
#define TYPE_002 std::unique_ptr<::toy::canvas::CodePrivate>

namespace toy{
namespace canvas{

class TOY_API_CANVAS Code
{
	public:

		/*
		 * type:
		 *   toy::VERTEX_SHADER
		 *   toy::FRAGMENT_SHADER
		 */
		Code(TYPE_001 brush, std::string filename, enum toy::Option type);
		Code(TYPE_001 brush, toy::Text&  code,     enum toy::Option type);

		~Code();

		bool isExist();
		auto brush()->TYPE_001;

	private:

		void drop();

		TYPE_002  _this;
		TYPE_001  _brush;

	public:

		auto _getShaderID()->uint32_t;  // Only work for graph::shader::Program
};

}}

#undef TYPE_002
#undef TYPE_001
