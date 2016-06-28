#pragma once

class AudioAdapter {

public:
	enum Sounds {
		ReadyStartGo, Blip, Noise, Powerup, Pickup, Tick
	};

	void Init();
	void Play(Sounds sound);

private:
	std::map<Sounds, sf::Sound*> _soundIndex;
};