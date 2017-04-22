#include <SFML/Graphics.hpp>
#include <vector>

#include "gameobjects.hpp"
#include "render.hpp"

Planet planet;

void UpdatePlanet(float delta_time, sf::RenderWindow * window) {

	if (planet.rotating) {
		planet.planet_sprite->setRotation(planet.planet_sprite->getRotation() + (((1280/2) - sf::Mouse::getPosition(*window).x) * 0.15 * delta_time));
	}

}

void UpdateGameObjects(float delta_time, sf::RenderWindow * window) {

	UpdatePlanet(delta_time, window);

}

void InitializeGameObjects() {

	// Planet
	sf::Texture * planet_texture = new sf::Texture;
	planet_texture->loadFromFile("../resources/planet.png");
	sf::Sprite * planet_sprite = new sf::Sprite;
	planet_sprite->setTexture(*planet_texture);
	planet_sprite->setOrigin(planet_sprite->getGlobalBounds().width / 2, planet_sprite->getGlobalBounds().height / 2);
	planet_sprite->setPosition(640, 720 + 700);
	planet.planet_sprite = planet_sprite;
	general_render_queue.push_back(planet_sprite);
	
}
