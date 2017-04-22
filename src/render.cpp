#include <SFML/Graphics.hpp>
#include <vector>

std::vector<sf::Drawable*> general_render_queue;
std::vector<sf::Drawable*> tower_render_queue;
std::vector<sf::Drawable*> enemy_render_queue;
std::vector<sf::Drawable*> bullet_render_queue;
std::vector<sf::Drawable*> ui_render_queue;