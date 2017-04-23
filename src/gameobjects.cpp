#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

#include "gameobjects.hpp"
#include "render.hpp"
#include "ui.hpp"
#include "sound.hpp"
#include "particles.hpp"

Planet planet;

sf::Texture * enemy_texture;
sf::Texture * bullet_texture;

std::vector<Tower*> towers;
std::vector<Enemy*> enemies; // @Refactor: Collapse this into enemy_render_queue?
std::vector<Bullet*> bullets;

float game_timer;
float spawn_cooldown;
uint8_t extra_towers_bitfield;

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

	Enemy * new_enemy = new Enemy;
	new_enemy->health = 100;
	sf::Sprite * new_enemy_sprite = new sf::Sprite;
	new_enemy->sprite = new_enemy_sprite;

	new_enemy_sprite->setTexture(*enemy_texture);
	new_enemy_sprite->setOrigin(new_enemy_sprite->getGlobalBounds().width / 2, new_enemy_sprite->getGlobalBounds().height / 2);

	float rotation = rand() % 360;
	sf::Vector2f spawn_pos = GetPositionAroundPlanet(rotation, 1280/2, 10); // second coord is inverse for some reason

	new_enemy_sprite->setPosition(spawn_pos);

	enemies.push_back(new_enemy);
	enemy_render_queue.push_back(new_enemy_sprite);

}

bool TowerCheck(sf::Vector2i mouse_pos) {

	int limit = towers.size();
	for (int i = 0; i < limit; i++) {
	
		if (towers[i]->sprite->getGlobalBounds().contains(
			static_cast<sf::Vector2f>(mouse_pos))) {
		
			tower_render_queue.erase(std::remove(tower_render_queue.begin(), tower_render_queue.end(), towers[i]->sprite));
			towers.erase(std::remove(towers.begin(), towers.end(), towers[i]));
			i--;
			limit--;

			return true;
		
		}

	}

	return false;

}

void ShootAtEnemy(Tower * tower, Enemy * target) {

	Bullet * new_bullet = new Bullet;
	sf::Sprite * new_bullet_sprite = new sf::Sprite;
	new_bullet_sprite->setTexture(*bullet_texture);
	new_bullet_sprite->setPosition(tower->sprite->getPosition());
	bullets.push_back(new_bullet);
	bullet_render_queue.push_back(new_bullet_sprite);

	shoot_sound->play();

	new_bullet->sprite = new_bullet_sprite;
	new_bullet->target = target;

}

void AddTower(sf::Vector2f pos, sf::Texture * texture) {

	Tower * new_tower = new Tower;
	sf::Sprite * new_tower_sprite = new sf::Sprite;
	new_tower->sprite = new_tower_sprite;
	new_tower->shoot_cooldown = 0;
	new_tower_sprite->setTexture(*texture);
	new_tower_sprite->setOrigin(new_tower_sprite->getGlobalBounds().width / 2, new_tower_sprite->getGlobalBounds().height / 2);

	// Position
	float vX = pos.x - planet.x_pos;
	float vY = pos.y - planet.y_pos;

	float magV = sqrt(vX*vX + vY*vY);

	float aX = planet.x_pos + vX / magV * planet.radius - 20;
	float aY = planet.y_pos + vY / magV * planet.radius - 20;

	// Rotation
	float angle = atan2(pos.y - planet.y_pos, pos.x - planet.x_pos);
	angle = angle * (180 / M_PI);
	angle += 180;
	angle -= 90;
	if (angle < 0)
		angle = 360 + angle;

	new_tower_sprite->setRotation(angle);
	new_tower_sprite->setPosition(aX,aY);
	towers.push_back(new_tower);
	tower_render_queue.push_back(new_tower_sprite);

}

void UpdateGameObjects(float delta_time, sf::RenderWindow * window) {

	game_timer += delta_time;
	spawn_cooldown -= delta_time;

	/************
	*** WAVES ***
	*************/

	if (enemies.size() < 7 && spawn_cooldown <= 0) {

		SpawnEnemy();
		float next_spawn_cooldown = 5 - (game_timer / 10);
		if (next_spawn_cooldown < 2)
			next_spawn_cooldown = 2;
		spawn_cooldown = next_spawn_cooldown;

	}

	if (game_timer > 10 && (extra_towers_bitfield & 1) == 0) {
		towers_left++;
		extra_towers_bitfield = extra_towers_bitfield | 1;
	}
	if (game_timer > 40 && (extra_towers_bitfield & (1 << 1)) == 0) {
		towers_left++;
		extra_towers_bitfield = extra_towers_bitfield | (1 << 1);
	}
	if (game_timer > 75 && (extra_towers_bitfield & (1 << 2)) == 0) {
		towers_left++;
		extra_towers_bitfield = extra_towers_bitfield | (1 << 2);
	}

	std::stringstream debug_text_stream;
	debug_text_stream << std::fixed << std::setprecision(1) << game_timer;
	debug_text->setString(debug_text_stream.str());

	float to_rotate = (((1280 / 2) - sf::Mouse::getPosition(*window).x) * 0.25 * delta_time);

	/********************
	*** PLANET/TOWERS ***
	*********************/

	// Deal with rotation of the planet
	if (planet.rotating) {
		planet.sprite->setRotation(
			planet.sprite->getRotation() + to_rotate);

		for (int i = 0; i < towers.size(); i++) {

			sf::Vector2f old_pos = towers[i]->sprite->getPosition();
			towers[i]->sprite->setPosition(planet.x_pos, planet.y_pos);
			towers[i]->sprite->setRotation(
				towers[i]->sprite->getRotation() + to_rotate);
			towers[i]->sprite->setPosition(old_pos);

			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);

			towers[i]->sprite->setPosition(rotated.x, rotated.y);

		}

	}

	// Every frame
	for (int i = 0; i < towers.size(); i++) {

		for (int j = 0; j < enemies.size(); j++) {

			if (sqrt(
				pow(towers[i]->sprite->getPosition().x - enemies[j]->sprite->getPosition().y, 2) +
				pow(towers[i]->sprite->getPosition().y - enemies[j]->sprite->getPosition().y, 2)) < 800) {

				if (towers[i]->shoot_cooldown <= 0) {
					ShootAtEnemy(towers[i], enemies[j]);
					towers[i]->shoot_cooldown = 0.1;
					break;
				}

			}

		}

		towers[i]->shoot_cooldown -= delta_time;

	}

	/****************
	**** ENEMIES ****
	*****************/

	// Deal with rotation of the planet
	if (planet.rotating) {

		for (int i = 0; i < enemies.size(); i++) {

			sf::Vector2f old_pos = enemies[i]->sprite->getPosition();
			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);
			enemies[i]->sprite->setPosition(rotated.x, rotated.y);

		}

	}

	// Every frame
	for (int i = 0; i < enemies.size(); i++) {

		auto epos = enemies[i]->sprite->getPosition();

		// Move towards planet
		sf::Vector2f move_vector;
		move_vector.x = planet.x_pos - epos.x;
		move_vector.y = planet.y_pos - epos.y;
		float mv_len = sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
		move_vector.x = move_vector.x / mv_len; // normalize
		move_vector.y = move_vector.y / mv_len;

		float time_multiplier = game_timer / 25;
		if (time_multiplier > 3)
			time_multiplier = 3;

		epos.x += (move_vector.x * 40 * delta_time * time_multiplier);
		epos.y += (move_vector.y * 40 * delta_time * time_multiplier);
		//epos.x += (move_vector.x * 500 * delta_time * time_multiplier);
		//epos.y += (move_vector.y * 500 * delta_time * time_multiplier);

		enemies[i]->sprite->setPosition(epos);

		// Spin
		enemies[i]->sprite->setRotation(
			enemies[i]->sprite->getRotation() + 200 * delta_time);

		// Check health
		if (enemies[i]->health <= 0) {
		
			crunch_sound->play();
			Explode(enemies[i]->sprite->getPosition(), 5.0);

			int limit = bullets.size();
			for (int b = 0; b < bullets.size(); b++) {

				if (bullets[b]->target == enemies[i]) {

					//bullet_render_queue.erase(std::remove(bullet_render_queue.begin(), bullet_render_queue.end(), bullets[b]->sprite));
					bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[b]));
					b--;
					limit--;

				}

			}

			enemy_render_queue.erase(std::remove(enemy_render_queue.begin(), enemy_render_queue.end(), enemies[i]->sprite));
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]));
			i--;

			continue;

		}

		// Check for planet collision
		if (sqrt(pow(planet.x_pos - epos.x, 2) + pow(planet.y_pos - epos.y, 2)) < 1020) {

			crunch_sound->play();
			Explode(enemies[i]->sprite->getPosition(), 5.0);

			for (int b = 0; b < bullets.size(); b++) {
			
				if (bullets[b]->target == enemies[i]) {
				
					//bullet_render_queue.erase(std::remove(bullet_render_queue.begin(), bullet_render_queue.end(), bullets[b]->sprite));
					bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]));
					b--;

				}

			}

			// @Refactor: It works, but there are better ways to do this that require redoing all of it
			enemy_render_queue.erase(std::remove(enemy_render_queue.begin(), enemy_render_queue.end(), enemies[i]->sprite));
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]));
			i--;

			planet.health -= 10;

		}

	}

	/****************
	**** BULLETS ****
	*****************/

	// Deal with rotation of the planet
	if (planet.rotating) {

		for (int i = 0; i < bullets.size(); i++) {

			sf::Vector2f old_pos = bullets[i]->sprite->getPosition();
			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);
			bullets[i]->sprite->setPosition(rotated.x, rotated.y);

		}

	}

	for (int i = 0; i < bullets.size(); i++) {
	
		sf::Vector2f bpos = bullets[i]->sprite->getPosition();
		sf::Vector2f tpos = bullets[i]->target->sprite->getPosition();

		// Move towards enemy
		sf::Vector2f move_vector;
		move_vector.x = tpos.x - bpos.x;
		move_vector.y = tpos.y - bpos.y;
		float mv_len = sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
		move_vector.x = move_vector.x / mv_len; // normalize
		move_vector.y = move_vector.y / mv_len;
		bpos.x += move_vector.x * 400 * delta_time;
		bpos.y += move_vector.y * 400 * delta_time;

		bullets[i]->sprite->setPosition(bpos);

		if (sqrt(pow(bpos.x - tpos.x, 2) + pow(bpos.y - tpos.y, 2)) < 1.0) {
		
			// Hit enemy
			bullets[i]->target->health -= 15.0;

			if (std::find(bullet_render_queue.begin(), bullet_render_queue.end(), bullets[i]->sprite) != bullet_render_queue.end()) {
				//bullet_render_queue.erase(std::remove(bullet_render_queue.begin(), bullet_render_queue.end(), bullets[i]->sprite));
			}
			if (std::find(bullets.begin(), bullets.end(), bullets[i]) != bullets.end()) {
				bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]));
			}
			i--;

		}

	}

	bullet_render_queue.clear();
	for (int i = 0; i < bullets.size(); i++) {
	
		bullet_render_queue.push_back(bullets[i]->sprite);

	}

}

void InitializeGameObjects() {

	// get rid of the biggest memory leaks god i am the worst programmer on this earth
	for (int i = 0; i < towers.size(); i++) {
		delete towers[i]->sprite;
	}
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i]->sprite;
	}
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i]->sprite;
	}

	towers.clear();
	enemies.clear();
	bullets.clear();

	game_timer = 0;

	extra_towers_bitfield = 0;

	// Enemy texture
	enemy_texture = new sf::Texture;
	enemy_texture->loadFromFile("../resources/grunt.png");

	// Bullet texture
	bullet_texture = new sf::Texture;
	bullet_texture->loadFromFile("../resources/bullet.png");

	// Planet
	sf::Texture * planet_texture = new sf::Texture;
	planet_texture->loadFromFile("../resources/planet.png");
	sf::Sprite * planet_sprite = new sf::Sprite;
	planet_sprite->setTexture(*planet_texture);
	planet_sprite->setOrigin(planet_sprite->getGlobalBounds().width / 2, planet_sprite->getGlobalBounds().height / 2);
	planet.x_pos = 640;
	planet.y_pos = 720 + 700;
	planet_sprite->setPosition(planet.x_pos, planet.y_pos);
	planet.sprite = planet_sprite;
	planet.radius = planet_sprite->getGlobalBounds().height / 2;
	planet.rotating = false;
	planet.health = 30;
	general_render_queue.push_back(planet_sprite);
	
}
