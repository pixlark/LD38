#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "gameobjects.hpp"
#include "render.hpp"

Planet planet;

std::vector<sf::Sprite*> towers;

void AddTower(sf::Vector2f pos, sf::Texture * texture) {

	sf::Sprite * new_tower = new sf::Sprite;
	new_tower->setTexture(*texture);
	new_tower->setOrigin(new_tower->getGlobalBounds().width / 2, new_tower->getGlobalBounds().height / 2);

	// Position
	float vX = pos.x - planet.x_pos;
	float vY = pos.y - planet.y_pos;

	float magV = sqrt(vX*vX + vY*vY);

	float aX = planet.x_pos + vX / magV * planet.radius;
	float aY = planet.y_pos + vY / magV * planet.radius;

	// Rotation
	float angle = atan2(pos.y - planet.y_pos, pos.x - planet.x_pos);
	angle = angle * (180 / M_PI);
	angle += 180;
	angle -= 90;
	if (angle < 0)
		angle = 360 + angle;

	new_tower->setRotation(angle);
	new_tower->setPosition(aX,aY);
	towers.push_back(new_tower);
	tower_draw_queue.push_back(new_tower);

}

void UpdatePlanet(float delta_time, sf::RenderWindow * window) {

	float to_rotate = (((1280 / 2) - sf::Mouse::getPosition(*window).x) * 0.15 * delta_time);

	if (planet.rotating) {
		planet.planet_sprite->setRotation(
			planet.planet_sprite->getRotation() + to_rotate);
	
		for (int i = 0; i < towers.size(); i++) {

			sf::Vector2f old_pos = towers[i]->getPosition();
			towers[i]->setPosition(planet.x_pos, planet.y_pos);
			towers[i]->setRotation(
				towers[i]->getRotation() + to_rotate);
			towers[i]->setPosition(old_pos);

			float to_rotate_rads = to_rotate * (M_PI / 180);
			
			float rotatedX = cos(to_rotate_rads) * (old_pos.x - planet.x_pos) - sin(to_rotate_rads) * (old_pos.y - planet.y_pos) + planet.x_pos;
			float rotatedY = sin(to_rotate_rads) * (old_pos.x - planet.x_pos) + cos(to_rotate_rads) * (old_pos.y - planet.y_pos) + planet.y_pos;

			towers[i]->setPosition(rotatedX, rotatedY);

		}
	
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
	planet.x_pos = 640;
	planet.y_pos = 720 + 700;
	planet_sprite->setPosition(planet.x_pos, planet.y_pos);
	planet.planet_sprite = planet_sprite;
	planet.radius = planet_sprite->getGlobalBounds().height / 2;
	planet.rotating = false;
	general_render_queue.push_back(planet_sprite);
	
}
