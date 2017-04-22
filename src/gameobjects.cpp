#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "gameobjects.hpp"
#include "render.hpp"

Planet planet;

sf::Texture * enemy_texture;

std::vector<sf::Sprite*> towers;
std::vector<sf::Sprite*> enemies;

sf::Vector2f GetPositionAroundPlanet(float degrees, sf::Vector2f start_pos) {

	sf::Vector2f rotated;

	float rads = degrees * (M_PI / 180);
	rotated.x = cos(rads) * (start_pos.x - planet.x_pos) - sin(rads) * (start_pos.y - planet.y_pos) + planet.x_pos;
	rotated.y = sin(rads) * (start_pos.x - planet.x_pos) + cos(rads) * (start_pos.y - planet.y_pos) + planet.y_pos;

	return rotated;

}

sf::Vector2f GetPositionAroundPlanet(float degrees, float start_x, float start_y) {

	sf::Vector2f rotated;

	float rads = degrees * (M_PI / 180);
	rotated.x = cos(rads) * (start_x - planet.x_pos) - sin(rads) * (start_y - planet.y_pos) + planet.x_pos;
	rotated.y = sin(rads) * (start_x - planet.x_pos) + cos(rads) * (start_y - planet.y_pos) + planet.y_pos;

	return rotated;

}

void SpawnEnemy() {

	sf::Sprite * new_enemy = new sf::Sprite;
	new_enemy->setTexture(*enemy_texture);
	new_enemy->setOrigin(new_enemy->getGlobalBounds().width / 2, new_enemy->getGlobalBounds().height / 2);

	float rotation = rand() % 360;
	sf::Vector2f spawn_pos = GetPositionAroundPlanet(rotation, 1280/2, 200);

	new_enemy->setPosition(spawn_pos);

	enemies.push_back(new_enemy);
	enemy_render_queue.push_back(new_enemy);

}

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
	tower_render_queue.push_back(new_tower);

}

void UpdatePlanet(float delta_time, sf::RenderWindow * window) {

	float to_rotate = (((1280 / 2) - sf::Mouse::getPosition(*window).x) * 0.15 * delta_time);

	// Deal with rotation of the planet
	if (planet.rotating) {
		planet.planet_sprite->setRotation(
			planet.planet_sprite->getRotation() + to_rotate);
	
		for (int i = 0; i < towers.size(); i++) {

			sf::Vector2f old_pos = towers[i]->getPosition();
			towers[i]->setPosition(planet.x_pos, planet.y_pos);
			towers[i]->setRotation(
				towers[i]->getRotation() + to_rotate);
			towers[i]->setPosition(old_pos);

			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);

			towers[i]->setPosition(rotated.x, rotated.y);

		}

		for (int i = 0; i < enemies.size(); i++) {

			sf::Vector2f old_pos = enemies[i]->getPosition();
			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);
			enemies[i]->setPosition(rotated.x, rotated.y);

		}
	
	}

	// Every frame
	for (int i = 0; i < enemies.size(); i++) {
	
		auto epos = enemies[i]->getPosition();

		// Move towards planet
		sf::Vector2f move_vector;
		move_vector.x = planet.x_pos - epos.x;
		move_vector.y = planet.y_pos - epos.y;
		float mv_len = sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
		move_vector.x = move_vector.x / mv_len; // normalize
		move_vector.y = move_vector.y / mv_len;
		epos.x += move_vector.x * 40 * delta_time;
		epos.y += move_vector.y * 40 * delta_time;

		enemies[i]->setPosition(epos);

		// Spin
		enemies[i]->setRotation(
			enemies[i]->getRotation() + 200 * delta_time);

	}

}

void UpdateGameObjects(float delta_time, sf::RenderWindow * window) {

	UpdatePlanet(delta_time, window);

}

void InitializeGameObjects() {

	// Enemy texture
	enemy_texture = new sf::Texture;
	enemy_texture->loadFromFile("../resources/grunt.png");

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
