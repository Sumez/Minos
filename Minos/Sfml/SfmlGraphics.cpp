#include "stdafx.h"
#include "../stdafx.h"
#include "../Game/DisplayGrid.h"
#include "../Game/Mino.h"
#include "SfmlGraphics.h"

SfmlGraphics::SfmlGraphics(sf::RenderTarget& renderWindow) {
	_renderTarget = &renderWindow;
	_rect = sf::RectangleShape(sf::Vector2f(1, 1));
};

void SfmlGraphics::Init() {
	_font = new sf::Font();
	_font->loadFromFile("square-deal.ttf");
};
void SfmlGraphics::LoadGameData() {
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

	MakeBgSprite("bg1.jpg");
	MakeBgSprite("bg2.jpg");
	MakeBgSprite("bg3.jpg");
	MakeBgSprite("bg4.jpg");
	MakeBgSprite("bg5.jpg");
};

void SfmlGraphics::MakeBgSprite(sf::String filename) {
	auto txBg = new sf::Texture();
	auto bgSprite = new sf::Sprite();
	txBg->loadFromFile(filename);
	bgSprite->setTexture(*txBg);
	double scale = (double)_renderTarget->getView().getSize().x / bgSprite->getLocalBounds().width;
	if (scale > 1) bgSprite->setScale(scale, scale);
	_backgrounds.push_back(bgSprite);
}

void SfmlGraphics::MakeColorSprite(MinoColors color, std::vector<unsigned> colorValues)  {
	auto sprite = sf::Sprite();
	const int borderWidth = 3;
	int b2 = 30 - borderWidth;

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
		sf::Vertex(sf::Vector2f(borderWidth, borderWidth), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(b2, borderWidth), sf::Color(colorValues[2])),
		sf::Vertex(sf::Vector2f(b2, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(borderWidth, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(borderWidth, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(b2, 15), sf::Color(colorValues[1])),
		sf::Vertex(sf::Vector2f(b2, b2), sf::Color(colorValues[0])),
		sf::Vertex(sf::Vector2f(borderWidth, b2), sf::Color(colorValues[0]))
	};

	txMinoCell->draw(rectangle, 8, sf::Quads);
	sprite.setTexture(txMinoCell->getTexture());

	_colorSprites.insert(std::pair<int, sf::Sprite>(color, sprite));
};

void SfmlGraphics::DrawText(std::string text, int x, int y, int size, unsigned color) {
	auto sfText = sf::Text(text, *_font, size);
	sfText.setPosition(x, y);
	sfText.setColor(sf::Color(color));
	_renderTarget->draw(sfText);
};

void SfmlGraphics::DrawSprite(sf::Sprite sprite) {
	sprite.setPosition(500, 100);
	_renderTarget->draw(sprite);
};

void SfmlGraphics::DrawMino(std::vector<std::vector<int>> coords) {
	for (int i = 0; i < 4; i++) {
		DrawCell(0, coords[i][0], coords[i][1], Red);
	};
};
void SfmlGraphics::DrawCell(DisplayGrid* grid, int x, int y, int color, double dark, CellMode modeFlags) {

	auto sprite = _colorSprites[color];
	auto blend = sf::Color(255, 255, 255);

	sprite.setPosition(x * grid->CellWidth + grid->X, y * grid->CellHeight + grid->Y);
	if (modeFlags & CellMode::Ghost || modeFlags & CellMode::Clearing) {
		blend.a = 51;
	}
	if (modeFlags & CellMode::Stack) {
		blend.r = blend.g = blend.b = 155;
	}
	if (dark > 0) {
		blend.r = blend.g = blend.b = 255 - 100 * dark;
	}
	sprite.setColor(blend);
	_renderTarget->draw(sprite);
};
void SfmlGraphics::DrawSymbol(DisplayGrid* grid, Symbol type, double opacity, double scale) {
	sf::String string;
	switch (type) {
	case Symbol::One:
		string = "1";
		break;
	case Symbol::Two:
		string = "2";
		break;
	case Symbol::Three:
		string = "3";
		break;
	case Symbol::Go:
		string = "GO";
	}
	auto sfText = sf::Text(string, *_font, 100);
	sfText.setPosition(
		grid->X + (grid->Width * grid->CellWidth - sfText.getLocalBounds().width * scale) / 2,
		grid->Y + (grid->Height * (grid->CellHeight - grid->InvisibleRows) - sfText.getLocalBounds().height * scale) / 2);
	sfText.setScale(scale, scale);
	sfText.setColor(sf::Color(255, 255, 255, 255 * opacity));
	_renderTarget->draw(sfText);
};

void SfmlGraphics::DrawOutline(DisplayGrid* grid, std::vector<std::vector<int>> buffer) {
	int bufferSize = buffer.size();
	std::vector<sf::Vertex> vertices;

	int outlineWidth = 2;
	int cWidth = grid->CellWidth;
	int cHeight = grid->CellHeight;
	int offsetX = grid->X;
	int offsetY = grid->Y + cHeight * grid->InvisibleRows;
	auto color = sf::Color(0xffffffff);

	for (int i = 0; i < bufferSize; i++) {
		int x = buffer[i][0] * cWidth + offsetX;
		int y = buffer[i][1] * cHeight + offsetY;
		int type = buffer[i][2];

		switch (type){
		case 0:
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y + outlineWidth), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y + outlineWidth), color));
			break;
		case 1:
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth - outlineWidth, y), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth - outlineWidth, y + cHeight), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y + cHeight), color));
			break;
		case 2:
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y + cHeight), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y + cHeight), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + cWidth, y + cHeight - outlineWidth), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y + cHeight - outlineWidth), color));
			break;
		case 3:
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y + cHeight), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + outlineWidth, y + cHeight), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x + outlineWidth, y), color));
			vertices.push_back(sf::Vertex(sf::Vector2f(x, y), color));
			break;
		}
	}

	_renderTarget->draw(&vertices[0], vertices.size(), sf::Quads);
};

void SfmlGraphics::DrawBackdrop(DisplayGrid* grid) {
	_rect.setSize(sf::Vector2f(grid->CellWidth * grid->Width, grid->CellHeight * (grid->Height - grid->InvisibleRows)));
	_rect.setPosition(grid->X, grid->Y + grid->InvisibleRows * grid->CellHeight);
	_rect.setFillColor(sf::Color(0, 0, 0, 200));
	_rect.setOutlineThickness(15);
	_rect.setOutlineColor(sf::Color(255, 255, 255));
	_renderTarget->draw(_rect);
};

void SfmlGraphics::DrawBackground(int index) {
	_renderTarget->draw(*_backgrounds[index]);
};

std::vector<int> SfmlGraphics::GetMousePosition() {
	auto hejhej = sf::Mouse::getPosition() - sf::Vector2i(-1394, 231);
	auto mpos = _renderTarget->mapPixelToCoords(hejhej);
	return { (int)mpos.x, (int)mpos.y };
}