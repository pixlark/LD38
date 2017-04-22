#include <SFML/Graphics.hpp>
#include <vector>

#include "render.hpp"
#include "ui.hpp"

sf::Font * default_font;
BuyButtons buy_buttons;
sf::Text * debug_text;

Cursors cursors;
sf::Sprite * cursor_sprite;

bool placing_tower = false;

void SetCursor(sf::Texture * cursor_texture) {

	cursor_sprite->setTexture(*cursor_texture);
	sf::IntRect texture_rect;
	texture_rect.left = 0;
	texture_rect.width = cursor_texture->getSize().x;
	texture_rect.top = 0;
	texture_rect.height = cursor_texture->getSize().y;
	cursor_sprite->setTextureRect(texture_rect);

}

bool ButtonCheck(sf::Vector2i mouse_pos) {

	if (buy_buttons.tower->getGlobalBounds().contains(
		static_cast<sf::Vector2f>(
			mouse_pos))) {
	
		SetCursor(cursors.tower_drag);
		placing_tower = true;
		return true;
	
	}

}

void UpdateUI(float delta_time, sf::RenderWindow * window) {

	cursor_sprite->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));
	
}

void InitializeUI() {

	// Get font
	default_font = new sf::Font;
	default_font->loadFromFile("../resources/Inconsolata.otf");

	// Get cursors
	cursors.default_cursor = new sf::Texture;
	cursors.default_cursor->loadFromFile("../resources/cursor.png");
	cursors.tower_drag = new sf::Texture;
	cursors.tower_drag->loadFromFile("../resources/tower.png");

	// Debug text
	debug_text = new sf::Text;
	debug_text->setFont(*default_font);
	debug_text->setColor(sf::Color::Black);
	debug_text->setCharacterSize(12);
	debug_text->setString("test");
	ui_render_queue.push_back(debug_text);

	// Basic tower button
	sf::Texture * ui_tower_texture = new sf::Texture;
	ui_tower_texture->loadFromFile("../resources/ui_tower.png");
	sf::Sprite * ui_tower_sprite = new sf::Sprite;
	ui_tower_sprite->setTexture(*ui_tower_texture);
	ui_tower_sprite->setPosition(0, 640);
	buy_buttons.tower = ui_tower_sprite;
	ui_render_queue.push_back(ui_tower_sprite);

	// Set cursor sprite
	cursor_sprite = new sf::Sprite;
	cursor_sprite->setTexture(*cursors.default_cursor);
	ui_render_queue.push_back(cursor_sprite);
	
}
