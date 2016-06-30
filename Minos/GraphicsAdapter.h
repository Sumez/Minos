#pragma once
#include "Game/Mino.h"
#include "Game/DisplayGrid.h"

enum CellMode {
	None = 0x00,
	Clearing = 0x01,
	Ghost = 0x02,
	Stack = 0x04,
	GameOver = 0x08
};
enum Symbol {
	Three, Two, One, Go
};
class GraphicsAdapter {
public:
	virtual void DrawText(std::string text, int x, int y, int size = 30, unsigned color = 0xffffffff) = 0;
	virtual void DrawSprite(sf::Sprite sprite) = 0;
	virtual void DrawMino(std::vector<std::vector<int>> coords) = 0;
	virtual void DrawCell(DisplayGrid* grid, int x, int y, int color, double dark = 0, CellMode modeFlags = CellMode::None) = 0;
	virtual void DrawSymbol(DisplayGrid* grid, Symbol type, double opacity, double size) = 0;
	virtual void DrawBackdrop(DisplayGrid* grid) = 0;
	virtual void DrawRectangle(int x1, int y1, int x2, int y2, unsigned color = 0x00000088) = 0;
	virtual void DrawOutline(DisplayGrid* grid, std::vector<std::vector<int>> buffer) = 0;
	virtual void DrawBackground(int index) = 0;
};