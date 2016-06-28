#pragma once
#include "../Windows/GraphicsAdapter.h"
#include "Mino.h"
#include "Randomizer.h"
#include "DisplayGrid.h"
#include "Settings.h"

class Game {

public:
	Game(GraphicsAdapter& graphics);
	void Init();
	void Update();
	void Draw();
	void Exit();

private:

	void ApplyInput(int rotate, int moveX, int moveY, bool sonicDrop, bool hardDrop);
	void ApplyGravity();
	void BeginSpawningNextMino(int delay);
	void ClearLines();

	bool TryMove(Mino & mino, int x, int y);
	bool TryRotate(Mino & mino, int direction);
	void UpdateGhost(Mino & mino);
	bool Collides(std::vector<std::vector<int>> & coords);
	bool Collides(Mino & mino, int x, int y);
	void LockMino(Mino & mino);
	bool IsLineSetToClear(int rowIndex);

	std::vector<std::vector<int>> _grid;
	std::vector<int> _rowsToClear;

	Randomizer _randomizer;
	GraphicsAdapter* _graphics;
	sf::Sprite _blockSprite = sf::Sprite();
	sf::Texture image;
	Mino _currentMino;
	Settings _settings;

	DisplayGrid _gameGrid;
	DisplayGrid _previewGrid;

	int spawnTimer;
	int lineClearTimer;
	int dasTimer;
	int dasState;

	bool _rLeft;
	bool _rRight;
};