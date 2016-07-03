#include "stdafx.h"
#include "../stdafx.h"
#include "Randomizer.h"
#include "Mino.h"

Randomizer::Randomizer(std::vector<int>* sequence) {
	_bag[0] = Mino::MinoType::I;
	_bag[1] = Mino::MinoType::Z;
	_bag[2] = Mino::MinoType::S;
	_bag[3] = Mino::MinoType::T;
	_bag[4] = Mino::MinoType::J;
	_bag[5] = Mino::MinoType::L;
	_bag[6] = Mino::MinoType::O;

	_sequence = sequence == NULL ? new std::vector<int>() : sequence;

	_history = std::vector<int>(4);
	_history[0] = 1;
	_history[1] = 2;
	_history[2] = 1;
	_history[3] = 2;

	_previews = std::vector<Mino::MinoType>(1);
	_previews[0] = GetRandomMino();

	std::srand(time(NULL));
};

bool Randomizer::IsInHistory(int find) {
	return std::find(_history.begin(), _history.end(), find) != _history.end();
};
Mino::MinoType Randomizer::GetMino() {
	auto newPiece = _previews[0];
	_previews[0] = GetRandomMino();
	return newPiece;
}
Mino::MinoType Randomizer::GetPreview(int index) {
	return _previews[index];
}

Mino::MinoType Randomizer::GetRandomMino() {
	int rngMaxTries = 6;
	int rngDummyResults = 0;

	int number = 7; // Initial dummy number forcing roll. Each roll might also result in a dummy number (if rngDummyResults > 0), always forcing another reroll

	if (_sequence->size() > _sequenceCounter)  {
		number = _sequence->at(_sequenceCounter);
	}
	else {

		int attempts = 0;

		while ((attempts < rngMaxTries && IsInHistory(number)) || number >= 7) {
			attempts++;
			int dummyAdd = rngDummyResults;
			if (attempts == rngMaxTries) dummyAdd = 0;
			number = std::rand() % (7 + dummyAdd);
		}
		_sequence->push_back(number);
	}
	_sequenceCounter++;

	_history.erase(_history.begin());
	_history.push_back(number);

	return _bag[number];
};
