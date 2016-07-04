#pragma once
#include "../GraphicsAdapter.h"
#include "../AudioAdapter.h"
#include "../InputHandler.h"
#include "GameWell.h"
#include "Replay.h"
#include "Menu.h"

class Session {
	
public:

	Session(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);

	GameWell Well;

	void Init(Replay* replay = NULL) { Well.Init(replay); };
	void Update();
	void Draw();
	Replay* GetReplay() { return Well.GetReplay(); };

private:

	Menu ReplayMenu;
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	InputHandler* _input;

};