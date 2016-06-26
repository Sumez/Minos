#pragma once
#include "../Windows/GraphicsAdapter.h"
#include "Mino.h"

class Game {

public:
	Game(GraphicsAdapter& graphics);
	void Init();
	void Update();
	void Draw();
	void Exit();

private:
	bool TryMove(Mino & mino, int x, int y);
	bool Collides(Mino & mino, int x, int y);

	GraphicsAdapter* _graphics;
	sf::Sprite _blockSprite = sf::Sprite();
	sf::Texture image;
	Mino _currentMino;

	int dasTimer;
	int dasState;
};