#include <SFML/Graphics.hpp>
#include <time.h>

#include "gameobjects.hpp"
#include "helpers.hpp"
#include "render.hpp"
#include "input.hpp"
#include "ui.hpp"
#include "music.hpp"
#include "sound.hpp"
#include "particles.hpp"
#include "state.hpp"

void RenderFromQueue(sf::RenderWindow * window, std::vector<sf::Drawable*> * queue) {

	for (int i = 0; i < queue->size(); i++) {
	
		window->draw(*(*queue)[i]);

	}

}

int main() {

	game_state = PLAYING; //

	srand(time(0));
	InitializeGameObjects();
	InitializeUI();
	InitializeAudio();
	InitializeParticles();
	StartMusic();
	
	sf::Image window_icon;
	window_icon.loadFromFile("../resources/icon.png");

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Planet Defense");
	window.setMouseCursorVisible(false);
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

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

		if (game_state == PLAYING) {
			UpdateGameObjects(delta_time, &window);
			UpdateUI(delta_time, &window);
			UpdateParticles(delta_time, &window);
		} else {
			UpdateCursor(&window);
		}

		window.clear(sf::Color::Black);
		window.draw(*starfield_sprite);
		RenderFromQueue(&window, &general_render_queue);
		RenderFromQueue(&window, &tower_render_queue);
		RenderFromQueue(&window, &enemy_render_queue);
		RenderFromQueue(&window, &bullet_render_queue);
		RenderFromQueue(&window, &particle_render_queue);
		RenderFromQueue(&window, &ui_render_queue);
		window.display();
		
	}
	
}
