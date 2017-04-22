#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>

sf::Vector2f CornerToCenterCoords(sf::Sprite sprite, sf::Vector2f pos);
sf::Vector2f CenterToCornerCoords(sf::Sprite sprite, sf::Vector2f pos);

#endif