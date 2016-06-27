#pragma once
#include "../Windows/GraphicsAdapter.h"
#include "Mino.h"
#include "Randomizer.h"

class Game {

public:
	Game(GraphicsAdapter& graphics);
	void Init();
	void Update();
	void Draw();
	void Exit();

private:

	void ApplyGravity();
	void BeginSpawningNextMino(int delay);

	bool TryMove(Mino & mino, int x, int y);
	bool Collides(Mino & mino, int x, int y);
	void LockMino(Mino & mino);

	std::vector<std::vector<int>> _grid;

	Randomizer _randomizer;
	GraphicsAdapter* _graphics;
	sf::Sprite _blockSprite = sf::Sprite();
	sf::Texture image;
	Mino _currentMino;

	int spawnTimer;
	int dasTimer;
	int dasState;

	bool _rLeft;
	bool _rRight;
};