#include "stdafx.h"
#include "../stdafx.h"
#include "GameWell.h"


GameWell::GameWell() {

}
GameWell::GameWell(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;
}

std::vector<int>* GameWell::GetSequence() {
	return _randomizer.GetSequence();
}

void GameWell::Init(std::vector<int>* sequence) {
	
	_randomizer = Randomizer(sequence);
	_grid = std::vector<std::vector<int>>(22, std::vector<int>(10));
	_rowsToClear = std::vector<int>(0);
	_firstMino = true;
	_frame = 0;
	_input->BeginRecording();
	_level = 0;
	_settings.SetLevel(0);
	_score = 0;
	_totalLines = 0;
	spawnTimer = 120;
	lineClearTimer = -1;
	UpdatePreview();

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

	_audio->Play(AudioAdapter::ReadyStartGo);
	_symbols.push_back(DisplayedSymbol(Three));
};

void GameWell::Update() {

	int rotate = 0;
	int moveX = 0;
	int moveY = 0;

	bool left = _input->IsHolding(InputHandler::P1Left);
	bool right = _input->IsHolding(InputHandler::P1Right);
	bool softDrop = _input->IsHolding(InputHandler::P1SoftDrop);
	bool sonicDrop = _input->IsHolding(InputHandler::P1SonicDrop);
	bool hardDrop = _input->IsHolding(InputHandler::P1HardDrop);

	bool rLeft = _input->IsHolding(InputHandler::P1RotateLeft);
	bool rRight = _input->IsHolding(InputHandler::P1RotateRight);
	if (left == right) left = right = false;

	if (rLeft && !_rLeft) { // TODO: check if mino exists
		rotate = -1;
	}
	if (rRight && !_rRight) { // TODO: check if mino exists
		rotate = 1;
	}
	
	if (!left && !right) {
		dasState = 0;
		dasTimer = 0;
	};
	if (left && dasState >= 0) {
		dasState = -1;
		dasTimer = _settings.DasCharge();
		moveX = dasState;
	};
	if (right && dasState <= 0) {
		dasState = 1;
		dasTimer = _settings.DasCharge();
		moveX = dasState;
	};
	if (dasState != 0) {
		if (dasTimer == 0) {
			dasTimer = _settings.DasRepeat();
			moveX = dasState;
		}
		dasTimer--;
	}

	if (softDrop) moveY = 1;

	if (spawnTimer >= 0) {
		spawnTimer--;

		if (_firstMino) {
			switch (spawnTimer) {
			case 80:
				_symbols.push_back(DisplayedSymbol(Two));
				break;
			case 40:
				_symbols.push_back(DisplayedSymbol(One));
				break;
			case 0:
				_symbols.push_back(DisplayedSymbol(Go));
				break;
			}
		}

		if (spawnTimer == 0) {
			SpawnMino(_randomizer.GetMino());
			UpdatePreview();
			spawnTimer = -1;
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
		ApplyGravity();
		ApplyInput(rotate, moveX, moveY, sonicDrop, hardDrop);
	}

	// Set these after spawn logic, to prevent double rotations when rotating on the exact frame a mino spawns (minor difference TODO: confirm this tgm behavior: frame perfect rotation can't prevent game over, like IRS could)
	_rLeft = rLeft;
	_rRight = rRight;

	int numSymbols = _symbols.size();
	for (int i = 0; i < numSymbols; i++) _symbols[i].Timer++;
	while (!_symbols.empty() && _symbols[0].Timer >= 40) _symbols.erase(_symbols.begin()); // Assumes the first symbol is always the oldest


	_input->AdvanceFrame();
	_frame++;
};

void GameWell::ApplyInput(int rotate, int moveX, int moveY, bool sonicDrop, bool hardDrop) {
	bool lock = false;
	// Important! Attempt rotations before moving left/right, to allow synchro moves
	if (rotate != 0 && TryRotate(_currentMino, rotate)) {
		if (_settings.LockReset() & Settings::RotateReset) _currentMino.LockTimer = 0;
	}
	if (moveX != 0 && TryMove(_currentMino, moveX, 0)) {
		if (_settings.LockReset() & Settings::MoveReset) _currentMino.LockTimer = 0;
	}
	if (moveY != 0) {
		if (TryMove(_currentMino, 0, moveY)) {
			_currentMino.DroppedDistance++;
			_currentMino.GravityTimer = 0;
			if (_settings.LockReset() & Settings::StepReset) _currentMino.LockTimer = 0;
		}
		else lock = true; // TODO: Not if SRS softdrop
	}
	if (sonicDrop || hardDrop) {
		int dropDistance = 0;
		while (!Collides(_currentMino, 0, dropDistance + 1)) dropDistance++;
		if (dropDistance > 0) {
			_currentMino.DroppedDistance += dropDistance;
			_currentMino.GravityTimer = 0;
			if (_settings.LockReset() & Settings::StepReset) _currentMino.LockTimer = 0;
		}
		_currentMino.Shift(0, dropDistance);
		_currentMino.SetGhostDistance(0);
		if (hardDrop) lock = true;
	}
	if (lock) LockMino(_currentMino);
};
void GameWell::UpdatePreview() {
	auto previewType = _randomizer.GetPreview(0);
	Mino preview = Mino(previewType);
	_previewMinoCoords = preview.GetCoords();
	_previewMinoColor = _settings.GetPieceColor(previewType);
}
void GameWell::SpawnMino(Mino::MinoType type) {
	if (!_firstMino && _settings.LevelOnSpawn() && (_level % 100 < 99) && _level < (_settings.MaxLevel() - 1)) IncreaseLevel(1); // TODO: Check level system + level stop

	_currentMino = Mino(type);
	_currentMino.Color = _settings.GetPieceColor(type);
	UpdateGhost(_currentMino);

	if (_settings.Irs()) {
		if (_rLeft) TryRotate(_currentMino, -1);
		if (_rRight) TryRotate(_currentMino, 1);
	}
	
	if (Collides(_currentMino.GetCoords())) {
		// TODO: Game over
	}
	_firstMino = 0;
}
void GameWell::IncreaseLevel(int amount) {
	_level += amount;
	if (_level >= _settings.MaxLevel()) {
		_level = _settings.MaxLevel();
		//TODO: Winning!
	}
	_settings.SetLevel(_level);
};
void GameWell::ApplyGravity() {

	if (_currentMino.IsLocking && !Collides(_currentMino, 0, 1)) _currentMino.IsLocking = false;
	if (_currentMino.IsLocking) { // Use STATE enum instead?
		_currentMino.GravityTimer = 0;
		// TODO: Get LockDelay based on function
		if (_currentMino.LockTimer >= _settings.LockDelay()) LockMino(_currentMino);
		_currentMino.LockTimer++;
	}
	else {
		_currentMino.GravityTimer += _settings.Gravity();
		while (_currentMino.GravityTimer >= _settings.GravityResolution()) {
			_currentMino.GravityTimer -= _settings.GravityResolution();
			if (TryMove(_currentMino, 0, 1)) {
				_currentMino.DroppedDistance = 0;
				_currentMino.IsLocking = false;
				if (_settings.LockReset() & Settings::StepReset) _currentMino.LockTimer = 0;
			}
			else {
				_currentMino.IsLocking = true;
				break;
			}
		}
	}
};

void GameWell::ClearLines() {
	int numRows = _rowsToClear.size();

	std::sort(_rowsToClear.begin(), _rowsToClear.end());
	int lowestRow = _rowsToClear[numRows - 1];

	for (int i = 0; i < numRows; i++) {
		for (int j = _rowsToClear[i]; j > 0; j--) {
			_grid[j] = _grid[j - 1];
		}
		_grid[0] = std::vector<int>(10);
	}
	_rowsToClear.clear();
	_audio->Play(AudioAdapter::Pickup);
	BeginSpawningNextMino(_settings.AreDelayOnLineClear(lowestRow));
};
void GameWell::LockMino(Mino & mino) {

	auto coords = mino.GetCoords();
	int lowestRow = 0;
	int clearedRows = 0;

	for (int i = 0; i < 4; i++) {
		int x = coords[i][0];
		int y = coords[i][1];
		if (y > lowestRow) lowestRow = y;

		_grid[y][x] = mino.Color;

		bool clearThisLine = true;
		for (int col = 0; col < 10; col++)
			if (_grid[y][col] == 0) clearThisLine = false;

		if (clearThisLine) {
			if (!IsLineSetToClear(y)) {
				_rowsToClear.push_back(y);
				clearedRows++;
			}
		}
	}
	if (clearedRows == 0) BeginSpawningNextMino(_settings.AreDelay(lowestRow));
	else {
		lineClearTimer = _settings.LineClearDelay();
		IncreaseTotalLines(clearedRows);
	}
	_audio->Play(AudioAdapter::Tick);
	AddScore(_settings.GetDropScore(mino.DroppedDistance));
	//inputHandler.ResetBuffers(); // Reset ARS and rotation buttons

	/*if (false) { // TODO: Test code to provoke error
		generateGarbage(1);
		for (int i = 0; i < rowsToClear.length; i++) {
			rowsToClear[i] = rowsToClear[i] - 1;
		}
	}*/
};
void GameWell::AddScore(int points) {
	_score += points;
};
void GameWell::IncreaseTotalLines(int lines) {
	_totalLines += lines;
	AddScore(_settings.GetLineClearScore(lines));
	IncreaseLevel(lines); //TODO: Depends on level system
};
bool GameWell::IsLineSetToClear(int rowIndex) {
	return std::find(_rowsToClear.begin(), _rowsToClear.end(), rowIndex) != _rowsToClear.end();
};
void GameWell::BeginSpawningNextMino(int delay) {

	spawnTimer = delay;

};

bool GameWell::TryMove(Mino & mino, int x, int y) {
	if (Collides(mino, x, y)) return false;
	mino.Shift(x, y);
	UpdateGhost(mino);
	return true;
};
bool GameWell::TryRotate(Mino & mino, int direction) {
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
void GameWell::UpdateGhost(Mino & mino) {
	int distance = 0;
	while (!Collides(mino, 0, distance + 1)) distance++;
	_currentMino.SetGhostDistance(distance);
};
bool GameWell::Collides(std::vector<std::vector<int>> & coords) {
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
bool GameWell::Collides(Mino & mino, int x, int y) {
	auto coords = mino.GetCoords();
	for (int i = 0; i < 4; i++) {
		coords[i][0] += x;
		coords[i][1] += y;
	}
	return Collides(coords);
};

void GameWell::Draw() {

	// Test textures
	//_graphics->DrawSprite(_blockSprite);

	// Draw well
	_graphics->DrawBackground(_level / 100);

	
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
			_graphics->DrawCell(&_gameGrid, coords[i][0], coords[i][1], _currentMino.Color, (double)_currentMino.LockTimer / _settings.LockDelay());
		};
	}

	// Draw white outline
	if (outlineBuffer.size() > 0) _graphics->DrawOutline(&_gameGrid, outlineBuffer);

	// draw Preview
	for (int i = 0; i < 4; i++) {
		_graphics->DrawCell(&_previewGrid, _previewMinoCoords[i][0], _previewMinoCoords[i][1], _previewMinoColor);
	};

	// Draw UI text
	_graphics->DrawText("Score", 450, 90);
	_graphics->DrawText(std::to_string(_score), 530, 90);

	_graphics->DrawText("Level", 450, 130);
	_graphics->DrawText(std::to_string(_level), 530, 130);

	_graphics->DrawText("Lines", 450, 170);
	_graphics->DrawText(std::to_string(_totalLines), 530, 170);

	// Draw symbols
	int numSymbols = _symbols.size();
	for (int i = 0; i < numSymbols; i++) {
		auto symbol = _symbols[i];
		_graphics->DrawSymbol(&_gameGrid, symbol.Type, 1 - (double)symbol.Timer / 40, 1 + (double)symbol.Timer / 40);
	}
};

void GameWell::Exit() {

};