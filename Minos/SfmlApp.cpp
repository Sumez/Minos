#pragma once
#include "stdafx.h"
#include <thread>
#include "SfmlApp.h"


void SfmlApp::LoadGameData() {
	_graphics->LoadGameData();
	_audio->LoadGameData();
	_loadedGameData = true;
}

void SfmlApp::Start(void)
{
	_graphics = new SfmlGraphics(_window);
	_audio = new SfmlAudio();
	_graphics->Init();
	_audio->Init();

	_window.create(sf::VideoMode(1024, 768, 32), "Minos");
	_window.setPosition(sf::Vector2i(-1400, 200));
	_window.setSize(sf::Vector2u(400, 300));

	_game = new Game(_graphics, _audio);
	auto loaderThread = std::thread(LoadGameData);

	sf::Clock clock = sf::Clock();
	sf::Time* elapsed;
	sf::Int64 counter = 0;
	while (!_exit)
	{
		elapsed = &clock.getElapsedTime();
		if (counter + elapsed->asMicroseconds() < 16666) continue;
		elapsed = &clock.restart();
		counter = elapsed->asMicroseconds();
#ifdef _DEBUG
		counter = 0; // Prevent "catching up" to slow frames while debugging
#endif
		GameLoop();
	}

	loaderThread.detach();
	_window.close();
}

void SfmlApp::GameLoop()
{
	sf::Event currentEvent;
	while (_window.pollEvent(currentEvent))
	{

		if (currentEvent.type == sf::Event::Closed)
		{
			_exit = true;
		}
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.alt && currentEvent.key.code == sf::Keyboard::Return) {
				_window.close();
				// TODO: Find supported video modes
				_window.create(sf::VideoMode(1024, 768, 32), "Minos", sf::Style::Fullscreen);
				_window.setMouseCursorVisible(false);
			}
			if (currentEvent.key.code == sf::Keyboard::Escape) _exit = true;
		}
	}

	if (_game->LoadedState == Game::Loading && _loadedGameData) _game->LoadedState = Game::Loaded;

	_game->Update();
	_window.clear(sf::Color(0, 0, 0));
	_game->Draw();
	_window.display();
}


SfmlGraphics* SfmlApp::_graphics = NULL;
SfmlAudio* SfmlApp::_audio = NULL;
bool SfmlApp::_loadedGameData = false;

bool SfmlApp::_exit = false;
sf::RenderWindow SfmlApp::_window;
Game* SfmlApp::_game = NULL;