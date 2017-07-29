
#pragma once

#include <SFML/Window.hpp>
#include "EventFunctorList.hpp"

extern bool HandleSystemEvent( const sf::Event&                   event,
                               EventFunctorList*                  functors,
                               std::function<void()>              closeWindow );
