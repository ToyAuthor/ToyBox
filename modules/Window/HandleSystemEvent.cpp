#include "HandleSystemEvent.hpp"

bool HandleSystemEvent( const sf::Event&                   event,
                        EventFunctorList*                  functors,
                        std::function<void()>              closeWindow )
{
	switch ( event.type )
	{
		case sf::Event::MouseMoved:
			return true;

		case sf::Event::MouseButtonPressed:
			return true;

		case sf::Event::MouseButtonReleased:
			return true;

		case sf::Event::KeyReleased:
			if ( event.key.code==sf::Keyboard::Escape )
			{
				closeWindow();
			}
			return true;

		case sf::Event::KeyPressed:
			return true;

		case sf::Event::Resized:
			functors->resize( event.size.width, event.size.height );
			return true;

		case sf::Event::Closed:
			closeWindow();
			return true;

		default:
			break;
	}

	return false;
}
