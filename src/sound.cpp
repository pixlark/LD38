#include <SFML/Audio.hpp>

sf::Sound * crunch_sound;

void InitializeAudio() {

	crunch_sound = new sf::Sound;
	sf::SoundBuffer * crunch_buffer = new sf::SoundBuffer;
	crunch_buffer->loadFromFile("../resources/crunch.wav");
	crunch_sound->setBuffer(*crunch_buffer);
	crunch_sound->setVolume(80);

}