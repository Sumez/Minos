#include "stdafx.h"
#include "../stdafx.h"
#include "game.h"


Game::Game(GraphicsAdapter& graphics) {
	_graphics = &graphics;
}

void Game::Init() {
	image = sf::Texture();
	if (!image.loadFromFile("test.jpg")) {
		throw "hej";
	}
	
	_randomizer = Randomizer();
	_grid = std::vector<std::vector<int>>(22, std::vector<int>(10));
	_blockSprite = sf::Sprite(image);
	spawnTimer = 120;
	_graphics->Init();
};

void Game::Update() {

	//Timing issues: rotate and move at the same time, which is executed first?

	int dasCharge = 14;
	int dasRepeat = 1;

	bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	bool rLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	bool rRight = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

	if (rLeft && !_rLeft) { // TODO: check if mino exists
		_currentMino.SetCoords(&_currentMino.GetRotated(-1));
	}
	if (rRight && !_rRight) { // TODO: check if mino exists
		_currentMino.SetCoords(&_currentMino.GetRotated(1));
	}
	_rLeft = rLeft;
	_rRight = rRight;

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

	if (spawnTimer >= 0) {
		spawnTimer--;
		if (spawnTimer == 0) {
			_currentMino = Mino(_randomizer.GetMino());
			spawnTimer = -1;
		}
	}
	else ApplyGravity();
};

void Game::ApplyGravity() {
	int gravityResolution = 256;
	int gravity = 10; // 5120;
	int lockDelay = 30;

	if (_currentMino.IsLocking && !Collides(_currentMino, 0, 1)) _currentMino.IsLocking = false;
	if (_currentMino.IsLocking) { // Use STATE enum instead?
		_currentMino.GravityTimer = 0;
		// TODO: Get LockDelay based on function
		if (_currentMino.LockTimer >= lockDelay) LockMino(_currentMino);
		_currentMino.LockTimer++;
	}
	else {
		_currentMino.GravityTimer += gravity;
		while (_currentMino.GravityTimer >= gravityResolution) {
			_currentMino.GravityTimer -= gravityResolution;
			if (TryMove(_currentMino, 0, 1)) {
				_currentMino.DroppedDistance = 0;
				_currentMino.IsLocking = false;
				_currentMino.LockTimer = 0; // TODO: If drop reset
			}
			else {
				_currentMino.IsLocking = true;
				break;
			}
		}
	}
};

void Game::LockMino(Mino & mino) {
	int areDelay = 25;

	auto coords = mino.GetCoords();
	int lowestRow = 0;
	for (int i = 0; i < 4; i++) {
		int x = coords[i][0];
		int y = coords[i][1];
		if (y > lowestRow) lowestRow = y;

		_grid[y][x] = 1; // get mino color

		bool clear = true;
		for (int col = 0; col < 10; col++)
			if (_grid[y][col] == 0) clear = false;

		if (clear) {
			/*if (typeof settings.lineClearDelay == 'string') timer = getTiming(settings.lineClearDelay, level);
			else timer = settings.lineClearDelay;
			state = gameState.CLEARING;
			if (rowsToClear.indexOf(y) == -1) rowsToClear.push(y);
			for (var col = 0; col < width; col++)
				rows[y][col] = colors.CLEARING;*/
		}
	}
	BeginSpawningNextMino(areDelay); // TODO: If not clearing rows  // TODO: Get-function based on lowest row of previous mino
	// sounds.lock.play();
	//addScore(dropDistance);
	//inputHandler.ResetBuffers(); // Reset ARS and rotation buttons

	/*if (false) { // TODO: Test code to provoke error
		generateGarbage(1);
		for (int i = 0; i < rowsToClear.length; i++) {
			rowsToClear[i] = rowsToClear[i] - 1;
		}
	}*/
};
void Game::BeginSpawningNextMino(int delay) {

	spawnTimer = delay;

};

bool Game::TryMove(Mino & mino, int x, int y) {
	if (Collides(mino, x, y)) return false;
	mino.Shift(x, y);
	return true;
};
bool Game::Collides(Mino & mino, int x, int y) {
	auto coords = mino.GetCoords();
	for (int i = 0; i < 4; i++) {
		int checkX = coords[i][0] + x;
		int checkY = coords[i][1] + y;

		if (checkY < 0) continue;
		if (checkX < 0) return true;
		if (checkX >= 10) return true;
		if (checkY >= 22) return true;
		if (_grid[checkY][checkX] > 0) return true;
	}
	return false;
};

void Game::Draw() {
	
	_graphics->DrawSprite(_blockSprite);
	
	if (spawnTimer < 0) // TODO: Keep track of active mino(s)
		_graphics->DrawMino(_currentMino.GetCoords());

	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 10; x++) {
			if (_grid[y][x] > 0) _graphics->DrawCell(x, y);
		}
	}
};

void Game::Exit() {


};