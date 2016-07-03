#pragma once
#include "../GraphicsAdapter.h"
#include "../AudioAdapter.h"
#include "../InputHandler.h"
#include "Mino.h"
#include "Randomizer.h"
#include "DisplayGrid.h"
#include "Settings.h"
#include <inttypes.h>

class GameWell {

public:
	
	GameWell(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* _input);
	GameWell();
	void Init(std::vector<int>* sequence = NULL);
	void Update();
	void Draw();
	void Exit();

	std::vector<int>* GetSequence();

private:

	struct DisplayedSymbol {
		Symbol Type;
		int Timer = 0;
		DisplayedSymbol(Symbol type) { Type = type; };
	};
	std::vector<DisplayedSymbol> _symbols;

	void ApplyInput(int rotate, int moveX, int moveY, bool sonicDrop, bool hardDrop);
	void ApplyGravity();
	void BeginSpawningNextMino(int delay);
	void ClearLines();
	void SpawnMino(Mino::MinoType);
	void IncreaseLevel(int amount);
	void AddScore(int points);
	void IncreaseTotalLines(int lines);
	void UpdatePreview();

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
	AudioAdapter* _audio;
	InputHandler* _input;
	Mino _currentMino;
	Settings _settings;

	DisplayGrid _gameGrid;
	DisplayGrid _previewGrid;

	int spawnTimer;
	int lineClearTimer;
	int dasTimer;
	int dasState;

	bool _firstMino;
	int _level;
	int _score;
	int _totalLines;
	bool _rLeft;
	bool _rRight;

	uint64_t _frame;

	std::vector<std::vector<int>> _previewMinoCoords = {};
	MinoColors _previewMinoColor = MinoColors::Empty;
};