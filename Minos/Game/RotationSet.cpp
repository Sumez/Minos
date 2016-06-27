#include "stdafx.h"
#include "../stdafx.h"
#include "RotationSet.h"

RotationSet::RotationSet() {
	RotationSet::Rotations = std::vector<std::vector<std::vector<int>>>(7, std::vector<std::vector<int>>(4, std::vector<int>(2)));
	Spawn = std::vector<int>(2);
	Spawn = { 4, 2 };
};

std::vector<std::vector<int>>* RotationSet::GetRotation(int index) {
	return &Rotations[index];
};