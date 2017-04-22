#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>

struct Planet {

	sf::Sprite * sprite;
	bool rotating;
	float radius;
	float x_pos;
	float y_pos;
	float health;
	
};

struct Tower {

	sf::Sprite * sprite;
	float shoot_cooldown;

};

struct Enemy {

	sf::Sprite * sprite;
	float health;

};

struct Bullet {

	sf::Sprite * sprite;
	Enemy * target;

};

extern Planet planet;

extern std::vector<Tower*> towers;

void SpawnEnemy();
void AddTower(sf::Vector2f pos, sf::Texture * texture);

void UpdateGameObjects(float delta_time, sf::RenderWindow * window);
void InitializeGameObjects();

#endif
