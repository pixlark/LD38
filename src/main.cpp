#include <SFML/Graphics.hpp>

#include "gameobjects.hpp"
#include "helpers.hpp"
#include "render.hpp"
#include "input.hpp"

int main() {

	InitializeGameObjects();
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "LD38");
	sf::Clock delta_time_clock;

	while (window.isOpen()) {

		float delta_time = delta_time_clock.getElapsedTime().asSeconds();
		delta_time_clock.restart();

		sf::Event window_event;
		while (window.pollEvent(window_event)) {

			ProcessInput(window_event, delta_time);
			
			switch (window_event.type) {

				case sf::Event::Closed: {

					window.close();
					
				} break;
				
			}
			
		}

		// Update functions
		UpdateGameObjects(delta_time);

		window.clear(sf::Color::White);
		for (int i = 0; i < general_render_queue.size(); i++) {
		
			window.draw(*general_render_queue[i]);

		}
		window.display();
		
	}
	
}
