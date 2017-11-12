
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Program.hpp"
#include "toy/graph/Array.hpp"

namespace toy{
namespace graph{
namespace _detail{

class Geometry
{
	public:

		Geometry(){}
		virtual ~Geometry(){}

		virtual void visible(bool show)=0;
		virtual bool isVisible() const=0;

		virtual void setModel(std::shared_ptr<toy::graph::Brush> brush,toy::graph::Array3<float> data)=0;
		virtual void setProgram(std::shared_ptr<toy::graph::Program> program)=0;
		virtual auto getProgram()->std::shared_ptr<toy::graph::Program> =0;

		virtual void bind(std::shared_ptr<toy::graph::Brush> brush)=0;
		virtual void render()=0;
};



}}}
