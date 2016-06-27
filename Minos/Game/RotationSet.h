#pragma once

class RotationSet {
public:
	RotationSet();
	int RotationCount = 4;
	std::vector<std::vector<int>>* GetRotation(int index);
	std::vector<int> Spawn;
	std::vector<std::vector<std::vector<int>>> Rotations;
};