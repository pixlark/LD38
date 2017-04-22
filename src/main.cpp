#include <SFML/Graphics.hpp>

#include "helpers.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(1280, 720), "LD38");

	sf::Texture planet_texture;
	planet_texture.loadFromFile("../resources/planet.png");
	
	sf::Sprite planet_sprite;
	planet_sprite.setTexture(planet_texture);
	sf::Vector2f center_pos;
	planet_sprite.setOrigin(planet_sprite.getGlobalBounds().width / 2, planet_sprite.getGlobalBounds().height / 2);
	planet_sprite.setPosition(640, 720 + 700);

	bool rotating = false;

	while (window.isOpen()) {

		sf::Event window_event;
		while (window.pollEvent(window_event)) {

			switch (window_event.type) {

				case sf::Event::Closed: {

					window.close();
					
				} break;

				case sf::Event::MouseButtonPressed: {

					rotating = true;

				} break;

				case sf::Event::MouseButtonReleased: {

					rotating = false;
					
				} break;
				
			}
			
		}

		if (rotating) {

			planet_sprite.setRotation(planet_sprite.getRotation() + 0.02);
			
		}

		window.clear(sf::Color::White);
		window.draw(planet_sprite);
		window.display();
		
	}
	
}
