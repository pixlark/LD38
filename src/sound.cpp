#include <SFML/Audio.hpp>

sf::Sound * crunch_sound;
sf::Sound * drill_sound;
sf::Sound * shoot_sound;
sf::Sound * unbuild_sound;

void InitializeAudio() {

	crunch_sound = new sf::Sound;
	sf::SoundBuffer * crunch_buffer = new sf::SoundBuffer;
	crunch_buffer->loadFromFile("../resources/crunch.wav");
	crunch_sound->setBuffer(*crunch_buffer);
	crunch_sound->setVolume(80);

	drill_sound = new sf::Sound;
	sf::SoundBuffer * drill_buffer = new sf::SoundBuffer;
	drill_buffer->loadFromFile("../resources/drill.wav");
	drill_sound->setBuffer(*drill_buffer);
	drill_sound->setVolume(65);

	shoot_sound = new sf::Sound;
	sf::SoundBuffer * shoot_buffer = new sf::SoundBuffer;
	shoot_buffer->loadFromFile("../resources/shoot.wav");
	shoot_sound->setBuffer(*shoot_buffer);
	shoot_sound->setVolume(50);

	unbuild_sound = new sf::Sound;
	sf::SoundBuffer * unbuild_buffer = new sf::SoundBuffer;
	unbuild_buffer->loadFromFile("../resources/un-build.wav");
	unbuild_sound->setBuffer(*unbuild_buffer);
	unbuild_sound->setVolume(60);

}