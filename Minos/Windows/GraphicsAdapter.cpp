#include "stdafx.h"
#include "../stdafx.h"
#include "../Game/DisplayGrid.h"
#include "GraphicsAdapter.h"

GraphicsAdapter::GraphicsAdapter(sf::RenderWindow& renderWindow) {
	_renderTarget = &renderWindow;
};

void GraphicsAdapter::Init() {

	auto txTest = new sf::Texture();
	txTest->loadFromFile("test.jpg");
	auto sprite = new sf::Sprite();
	sprite->setTexture(*txTest);

	MakeColorSprite(MinoColors::Red, { 0xff7777ff, 0xff0000ff, 0x990000ff });
	MakeColorSprite(MinoColors::Orange, { 0xffbb00ff, 0xff9900ff, 0xdd5500ff });
	MakeColorSprite(MinoColors::Green, { 0x44ff44ff, 0x00dd00ff, 0x007700ff });
	MakeColorSprite(MinoColors::Yellow, { 0xffff00ff, 0xffdd00ff, 0xaa9900ff });
	MakeColorSprite(MinoColors::Blue, { 0x44ccffff, 0x0099ffff, 0x0000ffff });
	MakeColorSprite(MinoColors::Cyan, { 0x00ffffff, 0x00bbbbff, 0x0099bbff });
	MakeColorSprite(MinoColors::Purple, { 0xff00ffff, 0xcc00ccff, 0x770077ff });
	MakeColorSprite(MinoColors::Gray, { 0xccccccff, 0x999999ff, 0x888888ff });

	_rect = sf::RectangleShape(sf::Vector2f(1, 1));
};

void GraphicsAdapter::MakeColorSprite(MinoColors color, std::vector<unsigned> colorValues)  {
	auto sprite = sf::Sprite();

	auto txMinoCell = new sf::RenderTexture();
	txMinoCell->create(30, 30);

	sf::Vertex border[] =
	{
		sf::Vertex(sf::Vector2f(0, 30), sf::Color(colorValues[0])),
		sf::Vertex(sf::Vector2f(30, 30), sf::Color(colorValues[0])),
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(colorValues[0])),
		sf::Vertex(sf::Vector2f(0, 0), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(30, 30), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(30, 0), sf::Color(colorValues[2])),
	};
	txMinoCell->draw(border, 6, sf::Triangles);

	sf::Vertex rectangle[] =
	{
		sf::Vertex(sf::Vector2f(2, 2), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(28, 2), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(28, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(2, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(2, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(28, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(28, 28), sf::Color(colorValues[0])),
		sf::Vertex(sf::Vector2f(2, 28), sf::Color(colorValues[0]))
	};

	txMinoCell->draw(rectangle, 8, sf::Quads);
	sprite.setTexture(txMinoCell->getTexture());

	_colorSprites.insert(std::pair<MinoColors, sf::Sprite>(color, sprite));
};

void GraphicsAdapter::DrawSprite(sf::Sprite sprite) {
	sprite.setPosition(500, 100);
	_renderTarget->draw(sprite);
};

void GraphicsAdapter::DrawMino(std::vector<std::vector<int>> coords) {
	for (int i = 0; i < 4; i++) {
		DrawCell(0, coords[i][0], coords[i][1]);
	};
};
void GraphicsAdapter::DrawCell(DisplayGrid* grid, int x, int y, CellMode modeFlags) {

	auto sprite = _colorSprites[MinoColors::Red];

	sprite.setPosition(x * grid->CellWidth + grid->X, y * grid->CellHeight + grid->Y);
	if (modeFlags & CellMode::Stack) {
		sprite.setColor(sf::Color(128, 128, 128));
	}
	else if (modeFlags & CellMode::Ghost || modeFlags & CellMode::Clearing) {
		sprite.setColor(sf::Color(255, 255, 255, 128));
	}
	else {
		sprite.setColor(sf::Color(255, 255, 255));
	}
	_renderTarget->draw(sprite);
};

void GraphicsAdapter::DrawBackdrop(DisplayGrid* grid) {
	_rect.setSize(sf::Vector2f(grid->CellWidth * grid->Width, grid->CellHeight * (grid->Height - grid->InvisibleRows)));
	_rect.setPosition(grid->X, grid->Y + grid->InvisibleRows * grid->CellHeight);
	_rect.setFillColor(sf::Color(0, 0, 0, 200));
	_rect.setOutlineThickness(15);
	_rect.setOutlineColor(sf::Color(255, 255, 255));
	_renderTarget->draw(_rect);
};