#pragma once
#include "Mino.h"

class Randomizer {

public:
	Randomizer();
	Mino::MinoType GetMino();
	Mino::MinoType GetPreview(int index);

private:
	Mino::MinoType _bag[7];
	std::vector<int> _history;
	std::vector<Mino::MinoType> _previews;

	Mino::MinoType GetRandomMino();
	bool IsInHistory(int find);
};