#include <SFML/Graphics.hpp>

#include "gameobjects.hpp"
#include "helpers.hpp"
#include "render.hpp"
#include "input.hpp"
#include "ui.hpp"

void RenderFromQueue(sf::RenderWindow * window, std::vector<sf::Drawable*> * queue) {

	for (int i = 0; i < queue->size(); i++) {
	
		window->draw(*(*queue)[i]);

	}

}

int main() {

	InitializeUI();
	InitializeGameObjects();
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "LD38");
	window.setMouseCursorVisible(false);

	sf::Clock delta_time_clock;

	while (window.isOpen()) {

		float delta_time = delta_time_clock.getElapsedTime().asSeconds();
		delta_time_clock.restart();

		sf::Event window_event;
		while (window.pollEvent(window_event)) {

			ProcessInput(window_event, delta_time, sf::Mouse::getPosition(window));
			
			switch (window_event.type) {

				case sf::Event::Closed: {

					window.close();
					
				} break;
				
			}
			
		}

		// Update functions
		UpdateGameObjects(delta_time, &window);
		UpdateUI(delta_time, &window);

		window.clear(sf::Color::White);
		RenderFromQueue(&window, &general_render_queue);
		RenderFromQueue(&window, &tower_draw_queue);
		RenderFromQueue(&window, &ui_render_queue);
		window.display();
		
	}
	
}
