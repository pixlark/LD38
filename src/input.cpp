#include <SFML/Graphics.hpp>

#include "gameobjects.hpp"

float rotate_origin_x;

void ProcessInput(sf::Event event, float delta_time) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed: {

			planet.rotating = true;
			planet.rotate_origin_x = sf::Mouse::getPosition().x;

		} break;

		case sf::Event::MouseButtonReleased: {

			planet.rotating = false;
					
		} break;
		
	}
	
} 
