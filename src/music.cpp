#include <SFML/Audio.hpp>

sf::Music * bg_music;

void StartMusic() {

	bg_music = new sf::Music;
	bg_music->openFromFile("../resources/music.wav");
	bg_music->setVolume(50);
	bg_music->setLoop(true);
	bg_music->play();

}