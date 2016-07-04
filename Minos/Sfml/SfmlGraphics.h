#pragma once
#include "../GraphicsAdapter.h"
#include "../Game/Mino.h"
#include "../Game/DisplayGrid.h"

class SfmlGraphics : public GraphicsAdapter {
public:
	SfmlGraphics(sf::RenderTarget& renderWindow);
	void DrawText(std::string text, int x, int y, int size = 30, unsigned color = 0xffffffff);
	void DrawSprite(sf::Sprite sprite);
	void DrawMino(std::vector<std::vector<int>> coords);
	void DrawCell(DisplayGrid* grid, int x, int y, int color, double dark = 0, CellMode modeFlags = CellMode::None);
	void DrawSymbol(DisplayGrid* grid, Symbol type, double opacity, double size);
	void DrawBackdrop(DisplayGrid* grid);
	void DrawRectangle(int x1, int y1, int x2, int y2, unsigned color = 0x00000088);
	void DrawOutline(DisplayGrid* grid, std::vector<std::vector<int>>& buffer);
	void DrawBackground(int index);
	void Init();
	void LoadGameData();
private:
	sf::RenderTarget* _renderTarget;
	sf::RectangleShape _rect;
	const int cellSize = 30;
	std::map<int, sf::Sprite> _colorSprites;
	void MakeColorSprite(MinoColors color, std::vector<unsigned> colorValues);
	void MakeBgSprite(sf::String filename);
	sf::Font* _font;
	std::vector<sf::Sprite*> _backgrounds;
};