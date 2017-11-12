
#pragma once

#include "toy/graph/Code.hpp"

namespace toy{
namespace graph{
class Brush;
struct ProgramPrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::graph::Brush>
#define TYPE_002 std::shared_ptr<::toy::graph::Code>
#define TYPE_003 struct ::toy::graph::ProgramPrivate*

namespace toy{
namespace graph{

class TOY_API_GRAPH Program
{
	public:

		Program(TYPE_002 vs,TYPE_002 fs);
		~Program();

		void use();
		void disuse();
		bool isUsed();

		auto getVertexShader()->TYPE_002;
		auto getFragmentShader()->TYPE_002;
		auto brush()->TYPE_001;

	private:

		TYPE_003   _this     = nullptr;
		TYPE_002   _vertex   = nullptr;
		TYPE_002   _fragment = nullptr;
		TYPE_001   _brush    = nullptr;

	public:

		void _use();            // Only work for toy::graph::Brush
		auto _id()->uint32_t;   // Work for "Uniform.hpp".
};

}}

#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
