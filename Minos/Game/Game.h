#pragma once
#include "../GraphicsAdapter.h"
#include "../AudioAdapter.h"
#include "GameWell.h"
#include "Menu.h"

class Game {
public:

	enum LoadedStates {
		Loading, Loaded
	};

	Game(GraphicsAdapter* graphics, AudioAdapter* audio);
	void Update();
	void Draw();

	LoadedStates LoadedState = Loading;

private:
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	std::vector<GameWell*> _activeWells;
	std::vector<Menu*> _activeMenus;
};