
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Export.hpp"

namespace toy{
namespace graph{
class  Brush;
struct CodePrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::graph::Brush>
#define TYPE_002 struct ::toy::graph::CodePrivate*

namespace toy{
namespace graph{

class TOY_API_GRAPH Code
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

		TYPE_002  _this  = nullptr;
		TYPE_001  _brush = nullptr;

	public:

		auto _getShaderID()->uint32_t;  // Only work for graph::shader::Program
};

}}

#undef TYPE_002
#undef TYPE_001
