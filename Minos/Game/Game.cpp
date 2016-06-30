#include "stdafx.h"
#include "../stdafx.h"
#include "MainMenu.h"
#include "Game.h"

Game::Game(GraphicsAdapter* graphics, AudioAdapter* audio) {
	_graphics = graphics;
	_audio = audio;

	auto mainMenu = new MainMenu(graphics, audio);
	mainMenu->StartNewGame = [&,this]() -> void {
		if (LoadedState != Loaded) return;
		auto newWell = new GameWell(_graphics, _audio);
		newWell->Init();
		_activeWells.push_back(newWell);
		_activeMenus.erase(_activeMenus.begin());
	};
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
}