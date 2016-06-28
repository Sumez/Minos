#include "stdafx.h"
#include "../stdafx.h"
#include "Game.h"


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
	_rowsToClear = std::vector<int>(0);
	_blockSprite = sf::Sprite(image);
	spawnTimer = 120;
	_graphics->Init();

	_gameGrid = DisplayGrid();
	_gameGrid.X = 100;
	_gameGrid.Y = 50;
	_gameGrid.CellWidth = 30;
	_gameGrid.CellHeight = 30;
	_gameGrid.Height = 22;
	_gameGrid.Width = 10;
	_gameGrid.InvisibleRows = 2;

	_previewGrid = DisplayGrid();
	_previewGrid.X = 100;
	_previewGrid.Y = -50;
	_previewGrid.CellWidth = 30;
	_previewGrid.CellHeight = 30;
	_previewGrid.Height = 4;
	_previewGrid.Width = 4;
};

void Game::Update() {

	//Timing issues: rotate and move at the same time, which is executed first?

	int dasCharge = 14;
	int dasRepeat = 1;

	int rotate = 0;
	int moveX = 0;
	int moveY = 0;

	bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool softDrop = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool sonicDrop = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool hardDrop = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	bool rLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	bool rRight = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

	if (rLeft && !_rLeft) { // TODO: check if mino exists
		rotate = -1;
	}
	if (rRight && !_rRight) { // TODO: check if mino exists
		rotate = 1;
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
		moveX = dasState;
	};
	if (right && dasState <= 0) {
		dasState = 1;
		dasTimer = dasCharge;
		moveX = dasState;
	};
	if (dasState != 0) {
		if (dasTimer == 0) {
			dasTimer = dasRepeat;
			moveX = dasState;
		}
		dasTimer--;
	}

	if (softDrop) moveY = 1;

	if (spawnTimer >= 0) {
		spawnTimer--;
		if (spawnTimer == 0) {
			auto minoType = _randomizer.GetMino();
			_currentMino = Mino(minoType);
			_currentMino.Color = _settings.GetPieceColor(minoType);
			UpdateGhost(_currentMino);
			spawnTimer = -1;

			// TODO: If IRS!
			if (_rLeft) TryRotate(_currentMino, -1);
			if (_rRight) TryRotate(_currentMino, 1);

			if (Collides(_currentMino.GetCoords())) {
				// TODO: Game over
			}
		}
	}
	if (lineClearTimer >= 0) {
		lineClearTimer--;
		if (lineClearTimer == 0) {
			ClearLines();
			lineClearTimer = -1;
		}
	}
	if (spawnTimer < 0 && lineClearTimer < 0) { // TODO: if Mino exists
		ApplyInput(rotate, moveX, moveY, sonicDrop, hardDrop);
		ApplyGravity();
	}
};

void Game::ApplyInput(int rotate, int moveX, int moveY, bool sonicDrop, bool hardDrop) {
	bool lock = false;
	if (rotate != 0) TryRotate(_currentMino, rotate);
	if (moveX != 0)  TryMove(_currentMino, moveX, 0);
	if (moveY != 0) {
		if (TryMove(_currentMino, 0, moveY)) {
			_currentMino.DroppedDistance++;
			_currentMino.GravityTimer = 0;
			_currentMino.LockTimer = 0; // TODO: If drop reset
		}
		else lock = true; // TODO: Not if SRS softdrop
	}
	if (sonicDrop || hardDrop) {
		int dropDistance = 0;
		while (!Collides(_currentMino, 0, dropDistance + 1)) dropDistance++;
		if (dropDistance > 0) {
			_currentMino.DroppedDistance += dropDistance;
			_currentMino.GravityTimer = 0;
			_currentMino.LockTimer = 0; // TODO: If drop reset
		}
		_currentMino.Shift(0, dropDistance);
		_currentMino.SetGhostDistance(0);
		if (hardDrop) lock = true;
	}
	if (lock) LockMino(_currentMino);
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

void Game::ClearLines() {
	int areDelay = 25;
	int numRows = _rowsToClear.size();

	std::sort(_rowsToClear.begin(), _rowsToClear.end());

	for (int i = 0; i < numRows; i++) {
		for (int j = _rowsToClear[i]; j > 0; j--) {
			_grid[j] = _grid[j - 1];
		}
		_grid[0] = std::vector<int>(10);
	}
	_rowsToClear.clear();
	BeginSpawningNextMino(areDelay); // TODO: Get-function based on the fact that this was a line clear
};
void Game::LockMino(Mino & mino) {
	int areDelay = 25;
	int lineClearDelay = 40;

	auto coords = mino.GetCoords();
	int lowestRow = 0;
	bool clearing = false;

	for (int i = 0; i < 4; i++) {
		int x = coords[i][0];
		int y = coords[i][1];
		if (y > lowestRow) lowestRow = y;

		_grid[y][x] = mino.Color;

		bool clearThisLine = true;
		for (int col = 0; col < 10; col++)
			if (_grid[y][col] == 0) clearThisLine = false;

		if (clearThisLine) {
			clearing = true;

			lineClearTimer = lineClearDelay;
			if (!IsLineSetToClear(y)) _rowsToClear.push_back(y);
			/* for (int col = 0; col < 10; col++) _grid[y][col] = 1; */ // don't set new color on row, use flag instead?
		}
	}
	if (!clearing) BeginSpawningNextMino(areDelay); // TODO: If not clearing rows  // TODO: Get-function based on lowest row of previous mino
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
bool Game::IsLineSetToClear(int rowIndex) {
	return std::find(_rowsToClear.begin(), _rowsToClear.end(), rowIndex) != _rowsToClear.end();
};
void Game::BeginSpawningNextMino(int delay) {

	spawnTimer = delay;

};

bool Game::TryMove(Mino & mino, int x, int y) {
	if (Collides(mino, x, y)) return false;
	mino.Shift(x, y);
	UpdateGhost(mino);
	return true;
};
bool Game::TryRotate(Mino & mino, int direction) {
	auto rotated = _currentMino.GetRotated(direction);
	if (Collides(rotated)) {
		if (!mino.SimpleWallkick) return false;
		for (int i = 0; i < 4; i++) rotated[i][0]++; // Then try moving right one
		if (Collides(rotated)) {
			for (int i = 0; i < 4; i++) rotated[i][0] -= 2; // Then try moving left one
			if (Collides(rotated)) return false;
		}
	}
	mino.SetCoords(&rotated);
	mino.RegisterRotation(direction);
	UpdateGhost(mino);
	return true;
};
void Game::UpdateGhost(Mino & mino) {
	int distance = 0;
	while (!Collides(mino, 0, distance + 1)) distance++;
	_currentMino.SetGhostDistance(distance);
};
bool Game::Collides(std::vector<std::vector<int>> & coords) {
	for (int i = 0; i < 4; i++) {
		int checkX = coords[i][0];
		int checkY = coords[i][1];

		if (checkY < 0) continue;
		if (checkX < 0) return true;
		if (checkX >= 10) return true;
		if (checkY >= 22) return true;
		if (_grid[checkY][checkX] > 0) return true;
	}
	return false;
};
bool Game::Collides(Mino & mino, int x, int y) {
	auto coords = mino.GetCoords();
	for (int i = 0; i < 4; i++) {
		coords[i][0] += x;
		coords[i][1] += y;
	}
	return Collides(coords);
};

void Game::Draw() {

	int lockDelay = 30;

	// Test textures
	_graphics->DrawSprite(_blockSprite);
	
	// Draw well
	_graphics->DrawBackdrop(&_gameGrid);

	// Draw stack
	std::vector<std::vector<int>> outlineBuffer;
	for (int y = 0; y < 22; y++) {
		int mode = CellMode::Stack;
		if (IsLineSetToClear(y)) mode = mode | CellMode::Clearing;
		for (int x = 0; x < 10; x++) {
			if (_grid[y][x] > 0) {
				_graphics->DrawCell(&_gameGrid, x, y, _grid[y][x], 0, static_cast<CellMode>(mode));
				if (y > 0 && _grid[y - 1][x] == 0) outlineBuffer.push_back({ x, y - 2, 0 });
				if (x < 10 - 1 && _grid[y][x + 1] == 0) outlineBuffer.push_back({ x, y - 2, 1 });
				if (y < 22 - 1 && _grid[y + 1][x] == 0) outlineBuffer.push_back({ x, y - 2, 2 });
				if (x > 0 && _grid[y][x - 1] == 0) outlineBuffer.push_back({ x, y - 2, 3 });
			}
		}
	}

	// draw Current Mino
	if (spawnTimer < 0 && lineClearTimer < 0) { // TODO: Keep track of active mino(s)

		auto coords = _currentMino.GetGhostCoords();
		for (int i = 0; i < 4; i++) {
			_graphics->DrawCell(&_gameGrid, coords[i][0], coords[i][1], _currentMino.Color, 0, CellMode::Ghost);
		};

		coords = _currentMino.GetCoords();
		for (int i = 0; i < 4; i++) {
			_graphics->DrawCell(&_gameGrid, coords[i][0], coords[i][1], _currentMino.Color, (double)_currentMino.LockTimer / lockDelay);
		};
	}

	// Draw white outline
	if (outlineBuffer.size() > 0) _graphics->DrawOutline(&_gameGrid, outlineBuffer);

	// draw Preview
	auto previewType = _randomizer.GetPreview(0);
	Mino preview = Mino(previewType);
	auto coords = preview.GetCoords();
	for (int i = 0; i < 4; i++) {
		_graphics->DrawCell(&_previewGrid, coords[i][0], coords[i][1], _settings.GetPieceColor(previewType));
	};
};

void Game::Exit() {

};