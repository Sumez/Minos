#include "stdafx.h"
#include "../stdafx.h"
#include "Mino.h"

Mino::Mino() {

	int initial[4][2] = { { 4, 2 }, { 5, 2 }, { 6, 2 }, { 5, 3 } };
	memcpy(_coords, initial, sizeof(initial));
};

std::vector<std::vector<int>> Mino::GetCoords() {
	std::vector<std::vector<int>> returnValue(4, std::vector<int>(2));
	for (int i = 0; i < 4; i++) {
		returnValue[i][0] = _coords[i][0];
		returnValue[i][1] = _coords[i][1];
	};
	return returnValue;
};

void Mino::Shift(int x, int y) {
	for (int i = 0; i < 4; i++) {
		_coords[i][0] += x;
		_coords[i][1] += y;
	};
};