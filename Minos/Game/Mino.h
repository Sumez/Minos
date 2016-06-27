#pragma once
#include "RotationSet.h"

class Mino {
public:
	enum MinoType {
		I, Z, S, T, J, L, O
	};
	Mino();
	Mino(MinoType type);
	std::vector<std::vector<int>> GetCoords();
	void SetCoords(std::vector<std::vector<int>>* newCoords);
	std::vector<std::vector<int>> GetRotated(int direction);
	void Shift(int x, int y);

	int Color = 0;
	int GravityTimer = 0;
	int LockTimer = 0;
	int DroppedDistance = 0;
	bool IsLocking = false;
	
private:
	void SetRotation(int rotationIndex);

	int _currentRotation = 0;
	int _coords[4][2];
	int _ghostCoords[4][2];
	RotationSet* _rotations;
};