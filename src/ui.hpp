#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

struct TextButton {

	sf::Sprite * sprite;
	sf::Text * text;

};

struct BuyButtons {

	sf::Sprite * tower;

};

struct Cursors {

	sf::Texture * default_cursor;
	sf::Texture * tower_drag;

};

extern BuyButtons buy_buttons;
extern Cursors cursors;
extern sf::Text * debug_text;

bool ButtonCheck(sf::Vector2i mouse_pos);
void UpdateUI(float delta_time, sf::RenderWindow * window);
void InitializeUI();

#endif
