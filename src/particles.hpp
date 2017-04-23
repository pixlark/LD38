#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>

struct Particle {

	sf::Sprite * sprite;
	float life;

};

void Explode(sf::Vector2f pos, float lifetime);
void UpdateParticles(float delta_time, sf::RenderWindow * window);
void InitializeParticles();

#endif