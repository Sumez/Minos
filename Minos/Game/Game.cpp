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
	_mainMenu->Add(new MenuItem("Begin game", [this]() -> void { _activeMenus.push_back(_gameTypeMenu); 	}));

	_mainMenu->Add(new MenuItem("Configuration", [this]() -> void {
		_activeMenus.push_back(_configMenu);
	}));
	_mainMenu->Add(new MenuItem("Replays", [this]() -> void {
		_activeMenus.push_back(_replayMenu);
	}));
	_mainMenu->Add(new MenuItem("Exit", [this]() -> void { Exiting = true; }));

	_gameTypeMenu = new Menu(_graphics, _audio, _input);
	_gameTypeMenu->Add(new MenuItem("Master", [this]() -> void { StartSession(Settings::Master); }));
	_gameTypeMenu->Add(new MenuItem("Old School", [this]() -> void { StartSession(Settings::OldSchool); }));
	_gameTypeMenu->Add(new MenuItem("Death", [this]() -> void { StartSession(Settings::Death); }));
	_gameTypeMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));
	
	_configMenu = new Menu(_graphics, _audio, _input);
	_configMenu->Add(new MenuItem("Controls", [this]() -> void {
		_activeMenus.push_back(_keyConfigMenu);
	}));
	_configMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));

	_replayMenu = new Menu(_graphics, _audio, _input);
	// TODO: Move to separate file, and only init when menu is displayed
	_replays = Replay::GetReplays(); // TODO: static list of replay or Delete replays when refreshing
	int replaySize = _replays.size();
	for (int i = 0; i < replaySize; i++) {
		ReplayHeader* replayHeader = &_replays[i];
		_replayMenu->Add(new MenuItem("A replay", [=]() -> void {
			if (LoadedState != Loaded) return;
			Replay* replay = new Replay(replayHeader->Filename); // TODO: Delete replay when done playing
			auto* newSession = new Session(_graphics, _audio, _input);
			newSession->Init(Settings::Master, replay); //TODO: Get settings from replay
			_activeSessions.push_back(newSession);
			while (_activeMenus.size()) _activeMenus.erase(_activeMenus.begin());
		}));
	}
	_replayMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));

	_keyConfigMenu = new ControlConfigMenu(_graphics, _audio, _input);
	_keyConfigMenu->Style = Menu::Small;
	_keyConfigMenu->Add(new MenuItem("Back", [this]() -> void { CloseMenu(); }));

	_ingameMenu = new Menu(_graphics, _audio, _input);
	_ingameMenu->Add(new MenuItem("Resume game", [this]() -> void {
		CloseMenu();
	}));
	_ingameMenu->Add(new MenuItem("Configuration", [this]() -> void {
		_activeMenus.push_back(_keyConfigMenu);
	}));
	_ingameMenu->Add(new MenuItem("Quit game", [this]() -> void {
		CloseMenu();
		_activeMenus.push_back(_mainMenu);
		delete _activeSessions[_activeSessions.size() - 1];
		_activeSessions.pop_back();
	}));

	_activeMenus.push_back(_mainMenu);
}

void Game::CloseMenu() {
	if (_activeMenus.size() <= 1 && _activeSessions.empty()) return;
	_activeMenus.pop_back();
}

void Game::Update() {

	int sessions = _activeSessions.size();
	for (int i = 0; i < sessions; i++){
		_activeSessions[i]->Update();
	}

	int menus = _activeMenus.size();
	if (menus > 0 && _input->JustPressed(InputHandler::CloseMenu)) {
		CloseMenu();
		menus = _activeMenus.size();
	}
	else if (menus == 0 && sessions > 0 && _input->JustPressed(InputHandler::OpenIngameMenu)) {
		_activeMenus.push_back(_ingameMenu);
		menus = _activeMenus.size();
	}
	
	if (!_activeMenus.empty()) _activeMenus[menus - 1]->Update();
}
void Game::Draw() {
	int wells = _activeSessions.size();
	for (int i = 0; i < wells; i++) {
		_activeSessions[i]->Draw();
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
void Game::StartSession(Settings::Preset preset) {
	if (LoadedState != Loaded) return;
	auto newSession = new Session(_graphics, _audio, _input);
	newSession->Init(preset);
	_activeSessions.push_back(newSession);
	_activeMenus.erase(_activeMenus.begin());
}