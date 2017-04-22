#include <SFML/Graphics.hpp>

sf::Vector2f CornerToCenterCoords(sf::Sprite sprite, sf::Vector2f pos) {

	sf::FloatRect bounds = sprite.getGlobalBounds();

	sf::Vector2f center_pos;

	center_pos.x = pos.x + (bounds.width / 2);
	center_pos.y = pos.y + (bounds.height / 2);
	
	return center_pos;
	
}

sf::Vector2f CenterToCornerCoords(sf::Sprite sprite, sf::Vector2f pos) {

	sf::FloatRect bounds = sprite.getGlobalBounds();

	sf::Vector2f corner_pos;

	corner_pos.x = pos.x - (bounds.width / 2);
	corner_pos.y = pos.y - (bounds.height / 2);
	
	return corner_pos;
	
}