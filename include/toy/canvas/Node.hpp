
#pragma once

#include "toy/canvas/NodeType.hpp"

namespace toy{
namespace canvas{
class Brush;

class Node
{
	public:

		virtual ~Node(){}

		bool same(enum ::toy::canvas::node::Type classType)
		{
			return _classType==classType;
		}

		virtual bool isVisible() const
		{
			return false;
		}

	protected:

		Node(enum ::toy::canvas::node::Type classType):_classType(classType){}

	private:

		enum ::toy::canvas::node::Type    _classType = ::toy::canvas::node::NONE_TYPE;

	public:

		virtual void _bind(){}
		virtual void _unbind(){}
		virtual void _render(::toy::canvas::Brush*,float){}
		virtual void _update(float){}
};

}}
