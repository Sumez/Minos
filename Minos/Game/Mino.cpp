#include "stdafx.h"
#include "../stdafx.h"
#include "RotationSet.h"
#include "Mino.h"

std::map<Mino::MinoType, RotationSet> rotationSystem;

Mino::Mino() {
};
Mino::Mino(MinoType type) {

	RotationSet tRotation;
	tRotation.Rotations = {
		{{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
		{{0, -1}, {0, 0}, {0, 1}, {-1, 0}},
		{{1, 1}, {0, 1}, {-1, 1}, {0, 0}},
		{{0, 1}, {0, 0}, {0, -1}, {1, 0}}
	};
	RotationSet iRotation;
	iRotation.Rotations = {
		{{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
		{{1, -1}, {1, 0}, {1, 1}, {1, 2}}
	};
	iRotation.RotationCount = 2;

	RotationSet lRotation;
	lRotation.Rotations = {
		{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}},
		{{0, -1}, {0, 0}, {0, 1}, {-1, -1}},
		{{1, 1}, {0, 1}, {-1, 1}, {1, 0}},
		{{0, 1}, {0, 0}, {0, -1}, {1, 1}}
	};
	RotationSet jRotation;
	jRotation.Rotations = {
		{{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
		{{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
		{{1, 1}, {0, 1}, {-1, 1}, {-1, 0}},
		{{0, 1}, {0, 0}, {0, -1}, {1, -1}}
	};
	RotationSet oRotation;
	oRotation.Rotations = {
		{{-1, 0}, {0, 0}, {-1, 1}, {0, 1}}
	};
	oRotation.RotationCount = 1;

	RotationSet sRotation;
	sRotation.Rotations = {
		{{1, 0}, {0, 0}, {0, 1}, {-1, 1}},
		{{-1, -1}, {-1, 0}, {0, 0}, {0, 1}}
	};
	sRotation.RotationCount = 2;

	RotationSet zRotation;
	zRotation.Rotations = {
		{{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
		{{1, -1}, {1, 0}, {0, 0}, {0, 1}}
	};
	zRotation.RotationCount = 2;

	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::T, tRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::I, iRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::L, lRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::J, jRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::O, oRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::S, sRotation));
	rotationSystem.insert(std::pair<Mino::MinoType, RotationSet>(Mino::MinoType::Z, zRotation));


	Color = 1;
	_rotations = &rotationSystem[type];

	int initial[4][2] = { { 4, 2 }, { 5, 2 }, { 6, 2 }, { 5, 3 } };
	memcpy(_coords, initial, sizeof(initial));

	SetRotation(_currentRotation);
	Shift(_rotations->Spawn[0], _rotations->Spawn[1]);
	/* memcpy(_coords, initialRotation, sizeof(initialRotation));*/};

void Mino::SetRotation(int rotationIndex) {
	_currentRotation = rotationIndex;
	SetCoords(_rotations->GetRotation(rotationIndex));
};

std::vector<std::vector<int>> Mino::GetRotated(int direction) {
	std::vector<std::vector<int>> returnValue(4, std::vector<int>(2));
	auto oldRotation =* _rotations->GetRotation(_currentRotation);
	_currentRotation += direction;
	
	if (_currentRotation >= _rotations->RotationCount) _currentRotation -= _rotations->RotationCount;
	if (_currentRotation < 0) _currentRotation += _rotations->RotationCount;
		auto newRotation =* _rotations->GetRotation(_currentRotation);	for (int i = 0; i < 4; i++) {

		int x, y;

		x = _coords[i][0] - oldRotation[i][0] + newRotation[i][0];
		y = _coords[i][1] - oldRotation[i][1] + newRotation[i][1];
		returnValue[i] = { x, y };
	}	return returnValue;
}

std::vector<std::vector<int>> Mino::GetCoords() {
	std::vector<std::vector<int>> returnValue(4, std::vector<int>(2));
	for (int i = 0; i < 4; i++) {
		returnValue[i][0] = _coords[i][0];
		returnValue[i][1] = _coords[i][1];
	};
	return returnValue;
};
void Mino::SetCoords(std::vector<std::vector<int>>* newCoords) {
	for (int i = 0; i < 4; i++) {
		_coords[i][0] = (*newCoords)[i][0];
		_coords[i][1] = (*newCoords)[i][1];
	};
};

void Mino::Shift(int x, int y) {
	for (int i = 0; i < 4; i++) {
		_coords[i][0] += x;
		_coords[i][1] += y;
	};
};