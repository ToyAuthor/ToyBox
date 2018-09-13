#include "HandleSystemEvent.hpp"

bool HandleSystemEvent( const sf::Event&                   event,
                        EventFunctorList*                  functors,
                        std::function<void()>              closeWindow )
{
	switch ( event.type )
	{
		case sf::Event::MouseMoved:
			break;

		case sf::Event::MouseButtonPressed:
			break;

		case sf::Event::MouseButtonReleased:
			break;

		case sf::Event::KeyReleased:
			if ( event.key.code==sf::Keyboard::Escape )
			{
				closeWindow();
				return false;
			}
			break;

		case sf::Event::KeyPressed:
			break;

		case sf::Event::Resized:
			functors->resize( event.size.width, event.size.height );
			break;

		case sf::Event::Closed:
			closeWindow();
			return false;

		default:
			break;
	}

	return true;
}
