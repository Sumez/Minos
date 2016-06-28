#pragma once
#include "RotationSet.h"

enum MinoColors {
	Empty = 0, Red, Orange, Green, Yellow, Blue, Cyan, Purple, Gray
};

class Mino {
public:
	enum MinoType {
		I, Z, S, T, J, L, O
	};
	Mino();
	Mino(MinoType type);
	std::vector<std::vector<int>> GetCoords();
	std::vector<std::vector<int>> GetGhostCoords();
	void SetCoords(std::vector<std::vector<int>>* newCoords);
	std::vector<std::vector<int>> GetRotated(int direction);
	void Shift(int x, int y);
	void SetGhostDistance(int height);
	void RegisterRotation(int direction);

	MinoColors Color;
	int GravityTimer = 0;
	int LockTimer = 0;
	int DroppedDistance = 0;
	bool IsLocking = false;
	bool SimpleWallkick;
	bool DrawGhost = true;
	
private:
	void SetRotation(int rotationIndex);
	int GetNewRotationIndex(int direction);

	int _currentRotation = 0;
	int _coords[4][2];
	int _ghostCoords[4][2];
	RotationSet* _rotations;
};