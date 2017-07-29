
#pragma once

#include <luapp.hpp>
#include <memory>
#include "EventFunctorList.hpp"

namespace sf
{
	class Window;
}

class ToySimpleWindow
{
	public:

		ToySimpleWindow(lua::Var table);
		~ToySimpleWindow(){}

		auto isOpen()->lua::Bool;
		void handleEvent();
		void display();
		auto good()->lua::Bool;

		void fullscreen(lua::Bool flag)
		{
			(void)flag;
		}

		lua::Str error()
		{
			return _errorMessage;
		}

	private:

		std::shared_ptr<sf::Window> _window = nullptr;
		lua::Str                    _errorMessage;
		EventFunctorList            _functorList;
};
