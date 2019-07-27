
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Array.hpp"
#include "toy/canvas/detail/Node.hpp"

namespace toy{
namespace canvas{
class Brush;
class Program;
namespace _detail{

class Geometry : public ::toy::canvas::_detail::Node
{
	public:

		Geometry():Node(::toy::canvas::node::GEOMETRY){}
		virtual ~Geometry(){}

		virtual void visible(bool show)=0;
		virtual bool isVisible() const=0;

		virtual void setModel(std::shared_ptr<toy::canvas::Brush> brush,toy::canvas::Array3<float> data)=0;
		virtual void setProgram(std::shared_ptr<toy::canvas::Program> program)=0;
		virtual auto getProgram()->std::shared_ptr<toy::canvas::Program> =0;

		virtual void bind(std::shared_ptr<toy::canvas::Brush> brush)=0;
		virtual void render()=0;
};

}}}
