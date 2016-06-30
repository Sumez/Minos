#pragma once
#include "Game\Game.h"
#include "Sfml/SfmlGraphics.h"
#include "Sfml/SfmlAudio.h"
#include "Sfml/SfmlInput.h"

class SfmlApp
{

public:
	static void Start();
	
private:
	static bool IsExiting();
	static void GameLoop();
	static void LoadGameData();

	static SfmlGraphics* _graphics;
	static SfmlAudio* _audio;
	static SfmlInput* _input;
	static bool _loadedGameData;

	static bool _exit;
	static Game* _game;
	static sf::RenderWindow _window;
};