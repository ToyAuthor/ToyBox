
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/ModelBuffer.hpp"
#include "toy/canvas/Texture.hpp"
#include "toy/canvas/detail/Node.hpp"

namespace toy{
namespace canvas{
class Brush;
class Program;
namespace _detail{

class Image : public ::toy::canvas::_detail::Node
{
	public:

		Image():Node(::toy::canvas::node::IMAGE){}
		virtual ~Image(){}

		virtual void visible(bool show)=0;
		virtual bool isVisible() const=0;

		virtual void setModel(std::shared_ptr<::toy::canvas::Brush> brush,const ::toy::canvas::ModelBuffer &data)=0;
		virtual void setTexture(::toy::canvas::Texture id)=0;
		virtual auto getTexture(int index)->::toy::canvas::Texture=0;
		virtual void pushMoreTexture(::toy::canvas::Texture id)=0;
		virtual void setProgram(std::shared_ptr<::toy::canvas::Program> program)=0;
		virtual auto getProgram()->std::shared_ptr<::toy::canvas::Program> =0;

		virtual void bind(std::shared_ptr<::toy::canvas::Brush> brush)=0;
		virtual void render(toy::canvas::Brush *brush,float diff)=0;
		virtual void update(float)=0;
		virtual void setPosition(const float*)=0;
};

}}}
