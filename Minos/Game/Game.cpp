#include "stdafx.h"
#include "../stdafx.h"
#include "MainMenu.h"
#include "ControlConfigMenu.h"
#include "Game.h"
#include "InputReplay.h"

Game::Game(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;

	_mainMenu = new MainMenu(graphics, audio, input);
	_mainMenu->Add(new MenuItem("Begin game", [&, this]() -> void {
		if (LoadedState != Loaded) return;
		auto newWell = new GameWell(_graphics, _audio, _input);
		newWell->Init();
		_activeWells.push_back(newWell);
		_activeMenus.erase(_activeMenus.begin());
	}));

	_mainMenu->Add(new MenuItem("Configuration", [this]() -> void {
		_activeMenus.push_back(_configMenu);
	}));
	_mainMenu->Add(new MenuItem("Exit", [this]() -> void { Exiting = true; }));

	_configMenu = new Menu(_graphics, _audio, _input);
	_configMenu->Add(new MenuItem("Controls", [this]() -> void {
		_activeMenus.push_back(_keyConfigMenu);
	}));
	_configMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));

	_keyConfigMenu = new ControlConfigMenu(_graphics, _audio, _input);
	_keyConfigMenu->Style = Menu::Small;
	_keyConfigMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));

	_ingameMenu = new Menu(_graphics, _audio, _input);
	_ingameMenu->Add(new MenuItem("Resume game", [this]() -> void {
		CloseMenu();
	}));
	_ingameMenu->Add(new MenuItem("Replay", [this]() -> void {
		CloseMenu();
		_activeMenus.push_back(_mainMenu);
		auto recordedSequence = _activeWells[_activeWells.size() - 1]->GetSequence();
		delete _activeWells[_activeWells.size() - 1];
		_activeWells.pop_back();

		auto replayWell = new GameWell(_graphics, _audio, new InputReplay(_input->GetRecording()));
		replayWell->Init(recordedSequence);
		_activeWells.push_back(replayWell);
	}));
	_ingameMenu->Add(new MenuItem("Configuration", [this]() -> void {
		_activeMenus.push_back(_keyConfigMenu);
	}));
	_ingameMenu->Add(new MenuItem("Quit game", [this]() -> void {
		CloseMenu();
		_activeMenus.push_back(_mainMenu);
		delete _activeWells[_activeWells.size() - 1];
		_activeWells.pop_back();
	}));

	_activeMenus.push_back(_mainMenu);
}

void Game::CloseMenu() {
	if (_activeMenus.size() <= 1 && _activeWells.empty()) return;
	_activeMenus.pop_back();
}

void Game::Update() {

	int wells = _activeWells.size();
	for (int i = 0; i < wells; i++){
		_activeWells[i]->Update();
	}

	int menus = _activeMenus.size();
	if (menus > 0 && _input->JustPressed(InputHandler::CloseMenu)) {
		CloseMenu();
		menus = _activeMenus.size();
	}
	else if (menus == 0 && wells > 0 && _input->JustPressed(InputHandler::OpenIngameMenu)) {
		_activeMenus.push_back(_ingameMenu);
		menus = _activeMenus.size();
	}
	
	if (!_activeMenus.empty()) _activeMenus[menus - 1]->Update();
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