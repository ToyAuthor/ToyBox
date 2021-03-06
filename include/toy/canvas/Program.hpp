
#pragma once

#include "toy/canvas/Code.hpp"

namespace toy{
namespace canvas{
class Brush;
struct ProgramPrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::canvas::Brush>
#define TYPE_002 std::shared_ptr<::toy::canvas::Code>
#define TYPE_003 std::unique_ptr<::toy::canvas::ProgramPrivate>

namespace toy{
namespace canvas{

class TOY_API_CANVAS Program
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

		TYPE_003   _this;
		TYPE_002   _vertex;
		TYPE_002   _fragment;
		TYPE_001   _brush;

	public:

		void _use();            // Only work for toy::canvas::Brush
		auto _id()->uint32_t;   // Work for "Uniform.hpp".
};

}}

#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
