#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>

struct Planet {

	sf::Sprite * planet_sprite;
	bool rotating;
	float radius;
	float x_pos;
	float y_pos;
	
};

extern Planet planet;

extern std::vector<sf::Sprite*> towers;

void AddTower(sf::Vector2f pos, sf::Texture * texture);

void UpdateGameObjects(float delta_time, sf::RenderWindow * window);
void InitializeGameObjects();

#endif
