#pragma once
#include "Mino.h"

class Randomizer {

public:
	Randomizer(std::vector<int>* sequence = NULL);
	Mino::MinoType GetMino();
	Mino::MinoType GetPreview(int index);

	std::vector<int>* GetSequence() { return _sequence; };

private:
	Mino::MinoType _bag[7];
	std::vector<int> _history;
	std::vector<Mino::MinoType> _previews;
	std::vector<int>* _sequence = NULL;
	int _sequenceCounter = 0;

	Mino::MinoType GetRandomMino();
	bool IsInHistory(int find);
};