#pragma once

class Mino {
public:
	Mino();
	std::vector<std::vector<int>> GetCoords();
	void Shift(int x, int y);

	int GravityTimer = 0;

private:
	int _coords[4][2];
};