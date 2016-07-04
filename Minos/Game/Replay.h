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
	Replay(std::vector<std::vector<InputHandler::ControlButton>>& input, std::vector<int>& minoSequence)
		:RecordedInput(input), MinoSequence(minoSequence) {

	};

	void Save();

	std::vector<std::vector<InputHandler::ControlButton>> RecordedInput;
	std::vector<int> MinoSequence;
};