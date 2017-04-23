#include <SFML/Graphics.hpp>
#include <vector>

#include "particles.hpp"
#include "render.hpp"
#include "gameobjects.hpp"

sf::Texture * explosion_texture;

std::vector<Particle> explosions;

void Explode(sf::Vector2f pos, float lifetime) {

	Particle new_particle;
	sf::Sprite * new_sprite = new sf::Sprite;
	new_sprite->setTexture(*explosion_texture);
	new_sprite->setOrigin(new_sprite->getGlobalBounds().width / 2, new_sprite->getGlobalBounds().height / 2);
	new_sprite->setPosition(pos);

	new_particle.sprite = new_sprite;
	new_particle.life = lifetime;
	explosions.push_back(new_particle);
	particle_render_queue.push_back(new_sprite);

}

void UpdateParticles(float delta_time, sf::RenderWindow * window) {

	float to_rotate = (((1280 / 2) - sf::Mouse::getPosition(*window).x) * 0.25 * delta_time);

	if (planet.rotating) {

		for (int i = 0; i < explosions.size(); i++) {

			sf::Vector2f old_pos = explosions[i].sprite->getPosition();
			sf::Vector2f rotated = GetPositionAroundPlanet(to_rotate, old_pos);
			explosions[i].sprite->setPosition(rotated.x, rotated.y);

		}

	}

	for (int i = 0; i < explosions.size(); i++) {

		sf::Color new_color = explosions[i].sprite->getColor();
		new_color.a -= 0.000000000045 * delta_time;
		explosions[i].sprite->setColor(new_color);

	}

}

void InitializeParticles() {

	explosion_texture = new sf::Texture;
	explosion_texture->loadFromFile("../resources/explosion.png");

}