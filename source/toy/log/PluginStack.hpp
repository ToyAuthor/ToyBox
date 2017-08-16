
#pragma once

#include <vector>

namespace toy{
namespace log{

template<typename T> class PluginStack
{
	public:
		PluginStack(){}
		~PluginStack(){}
};

template<typename T>
class PluginStack<std::function<void(const T*)>>
{
	public:

		typedef std::function<void(const T*)> FuncType;

		template<typename S>
		PluginStack(const S func)
		{
			_stack.push_back(FuncType(func));
		}

		~PluginStack(){}

		void operator ()(const T* str)
		{
			_stack.back()(str);
		}

		void push(FuncType func)
		{
			_stack.push_back(func);
		}

		void pop()
		{
			if (_stack.size()>1)
				_stack.pop_back();
		}

		void keepOne()
		{
			auto   size = _stack.size()-1;

			for ( ; size>0 ; size-- )
			{
				_stack.pop_back();
			}
		}

	private:

		std::vector<FuncType>    _stack;
};

}
}
