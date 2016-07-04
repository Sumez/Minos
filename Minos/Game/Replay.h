#pragma once
#include "../InputHandler.h"

struct ReplayHeader {
	ReplayHeader(std::wstring filename) : Filename(filename) {};

	std::wstring Filename;
	int BuildVersion;
};

class Replay {
public:

	static std::vector<ReplayHeader> GetReplays();

	Replay(std::wstring filename);
	Replay(std::vector<int>& input, std::vector<int>& minoSequence)
		:RecordedInput(input), MinoSequence(minoSequence) {

	};

	void Save();

	std::vector<int> RecordedInput;
	std::vector<int> MinoSequence;
};