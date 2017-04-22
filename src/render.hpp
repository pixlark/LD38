#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include <vector>

extern std::vector<sf::Drawable*> general_render_queue;
extern std::vector<sf::Drawable*> ui_render_queue;

#endif
