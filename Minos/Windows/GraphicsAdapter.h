#pragma once

class GraphicsAdapter {
public:
	GraphicsAdapter(sf::RenderWindow& renderWindow);
	void DrawSprite(sf::Sprite sprite);
	void DrawMino(std::vector<std::vector<int>> coords);
	void DrawCell(int x, int y);
	void Init();
private:
	sf::RenderTarget* _renderTarget;
	sf::Sprite _sprite2;
	const int cellSize = 30;
};