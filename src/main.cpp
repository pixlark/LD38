#include <SFML/Graphics.hpp>

int main() {

	sf::RenderWindow window(sf::VideoMode(1280, 720), "LD38");

	while (window.isOpen()) {

		sf::Event window_event;
		while (window.pollEvent(window_event)) {

			switch (window_event.type) {

				case sf::Event::Closed: {

					window.close();
					
				} break;
				
			}
			
		}
		
	}
	
}
