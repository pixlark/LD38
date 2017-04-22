#include <sstream>
#include <SFML/Graphics.hpp>

#include "gameobjects.hpp"
#include "ui.hpp"

float rotate_origin_x;

void ProcessInput(sf::Event event, float delta_time, sf::Vector2i mouse_pos) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed: {

			bool over_button = ButtonCheck(mouse_pos);

			std::stringstream debug_stream;
			debug_stream << over_button;
			debug_text->setString(debug_stream.str());

			if (!over_button) {

				planet.rotating = true;

			}

		} break;

		case sf::Event::MouseButtonReleased: {

			planet.rotating = false;
					
		} break;
		
	}
	
} 
