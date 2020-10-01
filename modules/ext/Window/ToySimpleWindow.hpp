
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
		auto handleEvent()->lua::Bool;
		void display();

		void fullscreen(lua::Bool flag)
		{
			(void)flag;
		}

	private:

		std::shared_ptr<sf::Window> _window = nullptr;
		EventFunctorList            _functorList;
};
