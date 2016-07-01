#include "stdafx.h"
#include "../stdafx.h"
#include "MainMenu.h"
#include "ControlConfigMenu.h"
#include "Game.h"

Game::Game(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;

	auto mainMenu = new MainMenu(graphics, audio, input);
	mainMenu->Add(new MenuItem("Begin game", [&,this]() -> void {
		if (LoadedState != Loaded) return;
		auto newWell = new GameWell(_graphics, _audio);
		newWell->Init();
		_activeWells.push_back(newWell);
		_activeMenus.erase(_activeMenus.begin());
	}));

	mainMenu->Add(new MenuItem("Configuration", [this]() -> void {
		auto configMenu = new Menu(_graphics, _audio, _input);
		configMenu->Add(new MenuItem("Controls", [this]() -> void {
			auto controlConfigMenu = new ControlConfigMenu(_graphics, _audio, _input);
			controlConfigMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));
			_activeMenus.push_back(controlConfigMenu);
		}));
		configMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));
		_activeMenus.push_back(configMenu);
	}));
	mainMenu->Add(new MenuItem("Exit", [this]() -> void { Exiting = true; }));

	_activeMenus.push_back(mainMenu);
}

void Game::CloseMenu() {
	_activeMenus.pop_back();
}

void Game::Update() {
	int wells = _activeWells.size();
	for (int i = 0; i < wells; i++){
		_activeWells[i]->Update();
	}

	if (!_activeMenus.empty()) _activeMenus[_activeMenus.size() - 1]->Update();
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