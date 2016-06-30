#pragma once
#include "../AudioAdapter.h"

class SfmlAudio : public AudioAdapter {

public:
	void Init();
	void LoadGameData();
	void Play(Sounds sound);

private:
	std::map<Sounds, sf::Sound*> _soundIndex;
};