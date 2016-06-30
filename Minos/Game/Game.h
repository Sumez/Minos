#pragma once
#include "../GraphicsAdapter.h"
#include "../AudioAdapter.h"
#include "../InputHandler.h"
#include "GameWell.h"
#include "Menu.h"

class Game {
public:

	enum LoadedStates {
		Loading, Loaded
	};

	Game(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);
	void Update();
	void Draw();

	bool Exiting = false;
	LoadedStates LoadedState = Loading;

private:
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	InputHandler* _input;
	std::vector<GameWell*> _activeWells;
	std::vector<Menu*> _activeMenus;
};