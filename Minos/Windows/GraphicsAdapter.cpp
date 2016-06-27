#include "stdafx.h"
#include "../stdafx.h"
#include "GraphicsAdapter.h"

GraphicsAdapter::GraphicsAdapter(sf::RenderWindow& renderWindow) {
	_renderTarget = &renderWindow;
};


void GraphicsAdapter::Init() {

	auto txTest = new sf::Texture();
	txTest->loadFromFile("test.jpg");
	auto sprite = new sf::Sprite();
	_sprite2 = sf::Sprite();
	sprite->setTexture(*txTest);

	auto txMinoCell = new sf::RenderTexture();
	txMinoCell->create(30, 30);
	txMinoCell->draw(*sprite);
	auto rect = sf::RectangleShape(sf::Vector2f(30, 30));
	rect.setFillColor(sf::Color(250, 200, 30));
	txMinoCell->draw(rect);
	rect.setSize(sf::Vector2f(26, 26));
	rect.setFillColor(sf::Color(250, 240, 80));
	rect.setPosition(2, 2);
	txMinoCell->draw(rect);
	_sprite2.setTexture(txMinoCell->getTexture());
};
void GraphicsAdapter::DrawSprite(sf::Sprite sprite) {
	sprite.setPosition(100, 100);
	_renderTarget->draw(sprite);
};

void GraphicsAdapter::DrawMino(std::vector<std::vector<int>> coords) {
	for (int i = 0; i < 4; i++) {
		DrawCell(coords[i][0], coords[i][1]);
		_renderTarget->draw(_sprite2);
	};
};
void GraphicsAdapter::DrawCell(int x, int y) {
	_sprite2.setPosition(x * cellSize, y * cellSize);
	_renderTarget->draw(_sprite2);
};