#include "stdafx.h"
#include "../stdafx.h"
#include "MainMenu.h"
#include "Game.h"

Game::Game(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;

	auto mainMenu = new MainMenu(graphics, audio, input);
	mainMenu->Add(MenuItem("Begin game", [&,this]() -> void {
		if (LoadedState != Loaded) return;
		auto newWell = new GameWell(_graphics, _audio);
		newWell->Init();
		_activeWells.push_back(newWell);
		_activeMenus.erase(_activeMenus.begin());
	}));

	mainMenu->Add(MenuItem("Configuration", []() -> void {}));
	mainMenu->Add(MenuItem("Exit", [this]() -> void { Exiting = true; }));

	_activeMenus.push_back(mainMenu);
}


void Game::Update() {
	int wells = _activeWells.size();
	for (int i = 0; i < wells; i++){
		_activeWells[i]->Update();
	}

	if (!_activeMenus.empty()) _activeMenus[0]->Update();
}
void Game::Draw() {
	int wells = _activeWells.size();
	for (int i = 0; i < wells; i++) {
		_activeWells[i]->Draw();
	}

	int menus = _activeMenus.size();
	for (int i = 0; i < menus; i++){
		_activeMenus[i]->Draw();
	}

	if (LoadedState == Loading) {

		_graphics->DrawRectangle(0, 720, 1024, 768, 0x88888888);
		_graphics->DrawText("Loading game data...", 20, 725);

	}
}