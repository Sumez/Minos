#include "stdafx.h"
#include "../stdafx.h"
#include "game.h"
#include "../Windows/GraphicsAdapter.h"


Game::Game(GraphicsAdapter& graphics) {
	_graphics = &graphics;
}

void Game::Init() {
	image = sf::Texture();
	if (!image.loadFromFile("test.jpg")) {
		throw "hej";
	}
	
	_blockSprite = sf::Sprite(image);
	_currentMino = Mino();
	_graphics->Init();
};

void Game::Update() {

	int dasCharge = 14;
	int dasRepeat = 1;
	int gravityResolution = 256;
	int gravity = 10; // 5120;

	bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	if (!left && !right) {
		dasState = 0;
		dasTimer = 0;
	};
	if (left && dasState >= 0) {
		dasState = -1;
		dasTimer = dasCharge;
		TryMove(_currentMino, dasState, 0);
	};
	if (right && dasState <= 0) {
		dasState = 1;
		dasTimer = dasCharge;
		TryMove(_currentMino, dasState, 0);
	};
	if (dasState != 0) {
		if (dasTimer == 0) {
			dasTimer = dasRepeat;
			TryMove(_currentMino, dasState, 0);
		}
		dasTimer--;
	}

	if (down) TryMove(_currentMino, 0, 1);

	_currentMino.GravityTimer += gravity;
	while (_currentMino.GravityTimer >= gravityResolution) {
		_currentMino.GravityTimer -= gravityResolution;
		TryMove(_currentMino, 0, 1);
	}
};

bool Game::TryMove(Mino & mino, int x, int y) {
	if (Collides(mino, x, y)) return false;
	mino.Shift(x, y);
	return true;
};
bool Game::Collides(Mino & mino, int x, int y) {
	auto coords = mino.GetCoords();
	for (int i = 0; i < 4; i++) {
		if (coords[i][0] + x < 0) return true;
		if (coords[i][0] + x >= 10) return true;
		if (coords[i][1] + y >= 22) return true;
	}
	return false;
};

void Game::Draw() {
	
	_graphics->DrawSprite(_blockSprite);

	int hejsa[4][2] = { { 4, 7 }, { 4, 8 }, { 4, 9 }, { 5, 8 } };
	_graphics->DrawMino(_currentMino.GetCoords());
};

void Game::Exit() {


};