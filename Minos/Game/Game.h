#pragma once
#include "../GraphicsAdapter.h"
#include "../AudioAdapter.h"
#include "../InputHandler.h"
#include "Session.h"
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
	void CloseMenu();
	void StartSession(Settings::Preset preset);

	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	InputHandler* _input;
	std::vector<Session*> _activeSessions;
	std::vector<Menu*> _activeMenus;

	Menu* _mainMenu;
	Menu* _gameTypeMenu;
	Menu* _configMenu;
	Menu* _replayMenu;
	Menu* _keyConfigMenu;
	Menu* _ingameMenu;


	std::vector<ReplayHeader> _replays;
};