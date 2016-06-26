#pragma once
#include "Game\Game.h"

class WindowsApp
{

public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static GameState _gameState;
	static Game _game;
	static sf::RenderWindow _mainWindow;
};