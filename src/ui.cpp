#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>

#include "render.hpp"
#include "ui.hpp"
#include "gameobjects.hpp"
#include "sound.hpp"
#include "particles.hpp"
#include "state.hpp"

sf::Font * default_font;
BuyButtons buy_buttons;
sf::Text * debug_text;
sf::Text * towers_text;
sf::Text * end_round_time_text;

sf::Sprite * starfield_sprite;

sf::Texture * default_button_texture;
sf::Sprite * game_over_sprite;
ProgressBar planet_health_bar;

Cursors cursors;
sf::Sprite * cursor_sprite;

int towers_left;

bool placing_tower = false;

void ResetCursor() {

	cursor_sprite->setTexture(*cursors.default_cursor);
	cursor_sprite->setOrigin(0, 0);
	sf::IntRect texture_rect;
	texture_rect.left = 0;
	texture_rect.width = cursors.default_cursor->getSize().x;
	texture_rect.top = 0;
	texture_rect.height = cursors.default_cursor->getSize().y;
	cursor_sprite->setTextureRect(texture_rect);

}

void SetCursor(sf::Texture * cursor_texture) {

	cursor_sprite->setTexture(*cursor_texture);
	cursor_sprite->setOrigin(cursor_sprite->getGlobalBounds().width / 2, cursor_sprite->getGlobalBounds().height / 2);
	sf::IntRect texture_rect;
	texture_rect.left = 0;
	texture_rect.width = cursor_texture->getSize().x;
	texture_rect.top = 0;
	texture_rect.height = cursor_texture->getSize().y;
	cursor_sprite->setTextureRect(texture_rect);

}

// @Refactor: Non-descriptive name
bool ButtonCheck(sf::Vector2i mouse_pos) {

	if (!placing_tower) {

		if (buy_buttons.tower->getGlobalBounds().contains(
			static_cast<sf::Vector2f>(
				mouse_pos))) {

			if (towers_left > 0) {

				SetCursor(cursors.tower_drag);
				placing_tower = true;
				towers_left--;

			}

			return true;

		} else {
			return false;
		}

	} else {
	
		ResetCursor();
		placing_tower = false;
		sf::Vector2f place_position = static_cast<sf::Vector2f>(mouse_pos);

		drill_sound->play();

		AddTower(place_position, cursors.tower_drag);

		return true;

	}

}

void UpdateCursor(sf::RenderWindow * window) {

	cursor_sprite->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));

}

void UpdateUI(float delta_time, sf::RenderWindow * window) {

	UpdateCursor(window);

	// Update health bar
	sf::Vector2f bar_size;
	bar_size.x = (planet.health * planet_health_bar.max_width) / planet_health_bar.max_value;
	bar_size.y = planet_health_bar.bar->getSize().y;
	if (bar_size.x >= 0) planet_health_bar.bar->setSize(bar_size);

	// Update towers left text
	std::stringstream towers_left_stream;
	towers_left_stream << towers_left;
	towers_text->setString(towers_left_stream.str());

	if (planet.health <= 0) { // game over
		ui_render_queue.push_back(game_over_sprite);
		std::stringstream ertt_stream;
		ertt_stream << "You defended for " << game_timer << " seconds";
		end_round_time_text->setString(ertt_stream.str());
		ui_render_queue.push_back(end_round_time_text);
		game_state = PAUSED;
	}

	if (planet.rotating) {
		float to_rotate = (((1280 / 2) - sf::Mouse::getPosition(*window).x) * 0.25 * delta_time);
		starfield_sprite->setRotation(starfield_sprite->getRotation() + (to_rotate / 4));
	}
	
}

void InitializeTextDefaults(sf::Text * text) {

	text->setFont(*default_font);
	text->setCharacterSize(24);
	text->setColor(sf::Color::Black);

}

void InitializeButton(
	TextButton * button,
	int x_pos, int y_pos,
	std::string button_text) {

	button->sprite->setTexture(*default_button_texture);
	button->sprite->setPosition(x_pos, y_pos);

	InitializeTextDefaults(button->text);
	button->text->setString(button_text);
	button->text->setPosition(x_pos + 10, y_pos + 8);

	ui_render_queue.push_back(button->sprite);
	ui_render_queue.push_back(button->text);

}

void InitializeUI() {

	// Get font
	default_font = new sf::Font;
	default_font->loadFromFile("../resources/Inconsolata.otf");

	// Get default textures
	default_button_texture = new sf::Texture;
	default_button_texture->loadFromFile("../resources/button.png");

	// Get cursors
	cursors.default_cursor = new sf::Texture;
	cursors.default_cursor->loadFromFile("../resources/cursor.png");
	cursors.tower_drag = new sf::Texture;
	cursors.tower_drag->loadFromFile("../resources/tower.png");

	// Debug text
	debug_text = new sf::Text;
	debug_text->setFont(*default_font);
	debug_text->setColor(sf::Color::White);
	debug_text->setCharacterSize(24);
	debug_text->setPosition(0, 50);
	debug_text->setString("test");
	ui_render_queue.push_back(debug_text);

	// Towers left text
	towers_text = new sf::Text;
	towers_text->setFont(*default_font);
	towers_text->setColor(sf::Color::White);
	towers_text->setCharacterSize(40);
	towers_text->setPosition(1240, 5);
	ui_render_queue.push_back(towers_text);
	towers_left = 1;

	// Game over screen
	sf::Texture * game_over_texture = new sf::Texture;
	game_over_texture->loadFromFile("../resources/game_over.png");
	game_over_sprite = new sf::Sprite;
	game_over_sprite->setTexture(*game_over_texture);

	// End round time text
	end_round_time_text = new sf::Text;
	end_round_time_text->setFont(*default_font);
	end_round_time_text->setColor(sf::Color::White);
	end_round_time_text->setOrigin(end_round_time_text->getGlobalBounds().width / 2, end_round_time_text->getOrigin().y);
	end_round_time_text->setPosition(1280 / 2, 600);

	// Round start button
	/*
	sf::Sprite * rsb_sprite = new sf::Sprite;
	sf::Text * rsb_text = new sf::Text;
	round_start_button.sprite = rsb_sprite;
	round_start_button.text = rsb_text;
	InitializeButton(&round_start_button, 1130, 630, "START");
	rsb_text->setColor(sf::Color::White);
	rsb_text->setCharacterSize(50);*/

	// Planet health bar
	sf::Texture * bar_bg_texture = new sf::Texture;
	bar_bg_texture->loadFromFile("../resources/bar_bg.png");
	sf::Sprite * bar_bg_sprite = new sf::Sprite;
	bar_bg_sprite->setTexture(*bar_bg_texture);
	sf::RectangleShape * bar_rect = new sf::RectangleShape;
	bar_rect->setPosition(6, 6);
	bar_rect->setFillColor(sf::Color::Red);
	sf::Vector2f bar_size;
	bar_size.x = 190;
	bar_size.y = 40;
	bar_rect->setSize(bar_size);

	planet_health_bar.bg = bar_bg_sprite;
	planet_health_bar.bar = bar_rect;
	planet_health_bar.max_value = 30;
	planet_health_bar.max_width = 190;
	
	ui_render_queue.push_back(bar_bg_sprite);
	ui_render_queue.push_back(bar_rect);

	// Basic tower button
	sf::Texture * ui_tower_texture = new sf::Texture;
	ui_tower_texture->loadFromFile("../resources/ui_tower.png");
	sf::Sprite * ui_tower_sprite = new sf::Sprite;
	ui_tower_sprite->setTexture(*ui_tower_texture);
	ui_tower_sprite->setPosition(0, 630);
	buy_buttons.tower = ui_tower_sprite;
	ui_render_queue.push_back(ui_tower_sprite);

	// Set cursor sprite
	cursor_sprite = new sf::Sprite;
	cursor_sprite->setTexture(*cursors.default_cursor);
	ui_render_queue.push_back(cursor_sprite);
	
	// Background starfield
	sf::Texture * starfield_texture = new sf::Texture;
	starfield_texture->loadFromFile("../resources/bg.png");
	starfield_sprite = new sf::Sprite;
	starfield_sprite->setTexture(*starfield_texture);
	starfield_sprite->setOrigin(starfield_sprite->getGlobalBounds().width / 2, starfield_sprite->getGlobalBounds().height / 2);
	starfield_sprite->setPosition(planet.sprite->getPosition());

}
