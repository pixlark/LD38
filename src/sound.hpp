#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

extern sf::Sound * crunch_sound;
extern sf::Sound * drill_sound;
extern sf::Sound * shoot_sound;
extern sf::Sound * unbuild_sound;

void InitializeAudio();

#endif