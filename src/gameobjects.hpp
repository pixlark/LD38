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

extern bool GAME_BEGUN;
extern std::vector<Tower*> towers;

sf::Vector2f GetPositionAroundPlanet(float degrees, sf::Vector2f start_pos);
sf::Vector2f GetPositionAroundPlanet(float degrees, float start_x, float start_y);

bool TowerCheck(sf::Vector2i mouse_pos);

void SpawnEnemy();
void AddTower(sf::Vector2f pos, sf::Texture * texture);

void UpdateGameObjects(float delta_time, sf::RenderWindow * window);
void InitializeGameObjects();

#endif
