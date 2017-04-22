#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>

struct Planet {

	sf::Sprite * planet_sprite;
	bool rotating;
	
};

extern Planet planet;

void UpdateGameObjects(float delta_time, sf::RenderWindow * window);
void InitializeGameObjects();

#endif
