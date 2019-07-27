
#pragma once

#include "toy/canvas/NodeType.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class Node
{
	public:

		virtual ~Node(){}

		bool same(enum ::toy::canvas::node::Type classType)
		{
			return _classType==classType;
		}

	protected:

		Node(enum ::toy::canvas::node::Type classType):_classType(classType){}

	private:

		enum ::toy::canvas::node::Type    _classType = ::toy::canvas::node::NONE_TYPE;
};

}}}
