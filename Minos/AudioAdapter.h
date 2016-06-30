#pragma once

class AudioAdapter {

public:
	enum Sounds {
		ReadyStartGo, Blip, Noise, Powerup, Pickup, Tick
	};

	virtual void LoadGameData() = 0;
	virtual void Play(Sounds sound) = 0;
};