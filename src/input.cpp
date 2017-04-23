#include <sstream>
#include <SFML/Graphics.hpp>

#include "gameobjects.hpp"
#include "ui.hpp"
#include "sound.hpp"

float rotate_origin_x;

void ProcessInput(sf::Event event, float delta_time, sf::Vector2i mouse_pos) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed: {

			if (event.mouseButton.button == sf::Mouse::Left) {

				bool over_button = ButtonCheck(mouse_pos);

				std::stringstream debug_stream;
				debug_stream << over_button;
				debug_text->setString(debug_stream.str());

				if (!over_button) {

					planet.rotating = true;

				}

			} else if (event.mouseButton.button == sf::Mouse::Right) {
			
				if (TowerCheck(mouse_pos)) {
					towers_left++;
					unbuild_sound->play();
				}

			}

		} break;

		case sf::Event::MouseButtonReleased: {

			if (event.mouseButton.button == sf::Mouse::Left) {

				planet.rotating = false;

			}
					
		} break;
		
	}
	
} 
