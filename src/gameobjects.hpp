#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>

struct Planet {

	sf::Sprite * planet_sprite;
	bool rotating;
	float rotate_origin_x;
	
};

extern Planet planet;

void UpdateGameObjects(float delta_time);
void InitializeGameObjects();

#endif
