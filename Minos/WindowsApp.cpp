#pragma once
#include "stdafx.h"
#include "WindowsApp.h"
#include "Game/Game.h"
#include "Windows/GraphicsAdapter.h"
#include "Windows/AudioAdapter.h"

void WindowsApp::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Minos");
	//_mainWindow.setPosition(sf::Vector2i(-1400, 200));
	//_mainWindow.setSize(sf::Vector2u(400, 300));
	GraphicsAdapter graphics = GraphicsAdapter(_mainWindow);
	AudioAdapter audio = AudioAdapter();
	graphics.Init();
	audio.Init();

	_game = Game(graphics, audio);
	_gameState = WindowsApp::Playing;
	_game.Init();

	sf::Clock clock = sf::Clock();
	sf::Time* elapsed;
	sf::Int64 counter = 0;
	while (!IsExiting())
	{
		elapsed = &clock.getElapsedTime();
		if (counter + elapsed->asMicroseconds() < 16666) continue;
		elapsed = &clock.restart();
		counter = elapsed->asMicroseconds();
		counter = 0; // Debugging
		GameLoop();
	}

	_mainWindow.close();
}

bool WindowsApp::IsExiting()
{
	if (_gameState == WindowsApp::Exiting)
		return true;
	else
		return false;
}

void WindowsApp::GameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent))
	{

		switch (_gameState)
		{
		case WindowsApp::Playing:
		{

			if (currentEvent.type == sf::Event::Closed)
			{
				_gameState = WindowsApp::Exiting;
			}
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.alt && currentEvent.key.code == sf::Keyboard::Return) {
					_mainWindow.close();
					_mainWindow.create(sf::VideoMode(1024, 768, 32), "Minos", sf::Style::Fullscreen);
					_mainWindow.setMouseCursorVisible(false);
				}
				if (currentEvent.key.code == sf::Keyboard::Escape) _gameState = WindowsApp::Exiting;
			}
			break;
		}
		}
	}
	_game.Update();
	_mainWindow.clear(sf::Color(100, 180, 255));
	_game.Draw();
	_mainWindow.display();
}


WindowsApp::GameState WindowsApp::_gameState = Uninitialized;
sf::RenderWindow WindowsApp::_mainWindow; 
Game WindowsApp::_game;