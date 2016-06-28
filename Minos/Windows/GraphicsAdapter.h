#pragma once
#include "../Game/Mino.h"
#include "../Game/DisplayGrid.h"

enum CellMode {
	None = 0x00,
	Clearing = 0x01,
	Ghost = 0x02,
	Stack = 0x04,
	GameOver = 0x08
};
class GraphicsAdapter {
public:
	GraphicsAdapter(sf::RenderWindow& renderWindow);
	void DrawSprite(sf::Sprite sprite);
	void DrawMino(std::vector<std::vector<int>> coords);
	void DrawCell(DisplayGrid* grid, int x, int y, int color, double dark = 0, CellMode modeFlags = CellMode::None);
	void DrawBackdrop(DisplayGrid* grid);
	void DrawOutline(DisplayGrid* grid, std::vector<std::vector<int>> buffer);
	void Init();
private:
	sf::RenderTarget* _renderTarget;
	sf::RectangleShape _rect;
	const int cellSize = 30;
	std::map<int, sf::Sprite> _colorSprites;
	void MakeColorSprite(MinoColors color, std::vector<unsigned> colorValues);
};