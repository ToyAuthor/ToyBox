
#pragma once

#include "toy/canvas/detail/Geometry.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class GcArrayBufferA;

#define PROGRAM_PTR  std::shared_ptr<toy::canvas::Program>
#define GEOMETRY_PTR std::shared_ptr<toy::canvas::_detail::GcArrayBufferA>

class GeometryA : public toy::canvas::_detail::Geometry
{
	public:

		GeometryA(std::shared_ptr<toy::canvas::Brush> brush);
		~GeometryA();

		void visible(bool show);
		bool isVisible() const;

		void setModel(std::shared_ptr<toy::canvas::Brush> brush,toy::canvas::Array3<float> data);
		void setProgram(std::shared_ptr<toy::canvas::Program> program);
		auto getProgram()->std::shared_ptr<toy::canvas::Program>;

		void bind(std::shared_ptr<toy::canvas::Brush> brush);
		void render();

	private:

		std::vector<float>   _data;
		GEOMETRY_PTR         _vList = nullptr;
		PROGRAM_PTR          _program = nullptr;
		bool                 _isVisible = false;
};

}}}

#undef GEOMETRY_PTR
#undef PROGRAM_PTR
