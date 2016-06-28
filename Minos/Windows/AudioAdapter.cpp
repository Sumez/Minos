#include "stdafx.h"
#include "../stdafx.h"
#include "AudioAdapter.h"

void AudioAdapter::Init() {

	auto blip = new sf::SoundBuffer();
	blip->loadFromFile("blip.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(Blip, new sf::Sound(*blip)));

	auto tick = new sf::SoundBuffer();
	tick->loadFromFile("tick.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(Tick, new sf::Sound(*tick)));

	auto ready = new sf::SoundBuffer();
	ready->loadFromFile("ready.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(ReadyStartGo, new sf::Sound(*ready)));

	auto noise = new sf::SoundBuffer();
	noise->loadFromFile("noise.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(Noise, new sf::Sound(*noise)));

	auto powerup = new sf::SoundBuffer();
	powerup->loadFromFile("powerup.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(Powerup, new sf::Sound(*powerup)));

	auto pickup = new sf::SoundBuffer();
	pickup->loadFromFile("pickup.wav");
	_soundIndex.insert(std::pair<Sounds, sf::Sound*>(Pickup, new sf::Sound(*pickup)));
};

void AudioAdapter::Play(Sounds sound) {
	_soundIndex[sound]->play();
};