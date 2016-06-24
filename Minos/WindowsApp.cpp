#include "stdafx.h"
#include "WindowsApp.h"

void WindowsApp::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Minos");
	_gameState = WindowsApp::Playing;

	sf::Clock clock = sf::Clock();
	sf::Time* elapsed;
	int counter = 0;
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
using namespace std;
void WindowsApp::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.clear(sf::Color(255, 0, 0));
	_mainWindow.display();
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
				if (currentEvent.key.code == sf::Keyboard::Escape) _gameState = WindowsApp::Exiting;
			}
			break;
		}
		}
	}
}


WindowsApp::GameState WindowsApp::_gameState = Uninitialized;
sf::RenderWindow WindowsApp::_mainWindow; 