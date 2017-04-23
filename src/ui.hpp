#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

struct ProgressBar {

	sf::Sprite * bg;
	sf::RectangleShape * bar;
	float max_value;
	float max_width;

};

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
extern int towers_left;

void UpdateCursor(sf::RenderWindow * window);
bool ButtonCheck(sf::Vector2i mouse_pos);
void UpdateUI(float delta_time, sf::RenderWindow * window);
void InitializeUI();

#endif
