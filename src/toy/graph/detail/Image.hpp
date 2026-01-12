
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/ModelBuffer.hpp"
#include "toy/graph/Texture.hpp"
#include "toy/graph/Program.hpp"

namespace toy{
namespace graph{
namespace _detail{

class Image
{
	public:

		Image(){}
		virtual ~Image(){}

		virtual void visible(bool show)=0;
		virtual bool isVisible() const=0;

		virtual void setModel(std::shared_ptr<::toy::graph::Brush> brush,const ::toy::graph::ModelBuffer &data)=0;
		virtual void setTexture(::toy::graph::Texture id)=0;
		virtual auto getTexture(int index)->::toy::graph::Texture=0;
		virtual void pushMoreTexture(::toy::graph::Texture id)=0;
		virtual void setProgram(std::shared_ptr<::toy::graph::Program> program)=0;
		virtual auto getProgram()->std::shared_ptr<::toy::graph::Program> =0;

		virtual void bind(std::shared_ptr<::toy::graph::Brush> brush)=0;
		virtual void render(toy::graph::Brush *brush,float diff)=0;
		virtual void update(float)=0;
};

}}}
