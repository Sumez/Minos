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
	_input = new SfmlInput();
	_input->Load();
	_graphics->Init();
	_audio->Init();

	_window.create(sf::VideoMode(1024, 768, 32), "Minos");
	//_window.setPosition(sf::Vector2i(-1400, 200));
	//_window.setSize(sf::Vector2u(400, 300));

	_game = new Game(_graphics, _audio, _input);
	auto loaderThread = std::thread(LoadGameData);

	sf::Clock clock = sf::Clock();
	sf::Int64 counter = 0;

	while (!_exit)
	{
		counter += clock.restart().asMicroseconds();
		if (counter < 16666) continue;
		counter -= 16666;
		GameLoop();
#ifdef _DEBUG
		_graphics->DrawText(std::to_string(counter), 600, 50);
		_window.display();
		counter = 0; // Prevent "catching up" to slow frames while debugging
#endif
	}

	loaderThread.detach();
	_window.close();
}

void SfmlApp::GameLoop()
{
	_input->Clear();
	sf::Event currentEvent;
	while (_window.pollEvent(currentEvent))
	{

		switch (currentEvent.type)
		{
		case sf::Event::JoystickMoved:
			_input->MovedJoystick(currentEvent.joystickMove.joystickId, currentEvent.joystickMove.axis, currentEvent.joystickMove.position);
			break;
		case sf::Event::JoystickButtonPressed:
			_input->PressedJoystickButton(currentEvent.joystickButton.joystickId, currentEvent.joystickButton.button);
			break;
		case sf::Event::JoystickButtonReleased:
			_input->ReleasedJoystickButton(currentEvent.joystickButton.joystickId, currentEvent.joystickButton.button);
			break;
		case sf::Event::MouseButtonPressed:
			_input->ClickedMouse(currentEvent.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			_input->UnclickedMouse(currentEvent.mouseButton.button);
			break;
		case sf::Event::KeyPressed:
			_input->PressedKey(currentEvent.key.code);
			break;
		case sf::Event::KeyReleased:
			_input->ReleasedKey(currentEvent.key.code);
			break;

		case sf::Event::Closed:
			_exit = true;
			break;
		}

		if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.alt && currentEvent.key.code == sf::Keyboard::Return)
		{
			_window.close();
			// TODO: Find supported video modes
			_window.create(sf::VideoMode(1024, 768, 32), "Minos", sf::Style::Fullscreen);
			//_window.setMouseCursorVisible(false);
		}
	}
	_input->MovedMouse(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)));
	if (_game->LoadedState == Game::Loading && _loadedGameData) _game->LoadedState = Game::Loaded;

	_game->Update();
	_window.clear(sf::Color(0, 0, 0));
	_game->Draw();
	//_window.display();

	if (_game->Exiting) _exit = true;
}


SfmlGraphics* SfmlApp::_graphics = NULL;
SfmlAudio* SfmlApp::_audio = NULL;
SfmlInput* SfmlApp::_input = NULL;
bool SfmlApp::_loadedGameData = false;

bool SfmlApp::_exit = false;
sf::RenderWindow SfmlApp::_window;
Game* SfmlApp::_game = NULL;