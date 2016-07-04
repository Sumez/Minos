#include "stdafx.h"
#include "../stdafx.h"
#include "Replay.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <ShlObj.h>
#include <Windows.h>
#include <inttypes.h>


std::wstring ReplayFile() {
	std::wstringstream ss;
	PWSTR path = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path)))
	{
		ss << path << "\\Minos\\";
		CreateDirectory(ss.str().c_str(), NULL); // Fails if exists, but no one cares
		ss << "Replays\\";
		CreateDirectory(ss.str().c_str(), NULL); // Fails if exists, but no one cares
	}
	ss << std::to_wstring(time(NULL)) << ".rpl";
	return ss.str();
}
void Replay::Save() {
	
	std::ofstream file;
	errno = 0;
	file.open(ReplayFile(), std::ios::out | std::ios::trunc | std::ios::binary);
	
	if (errno) return;

	char headerSize = 1;
	file.write(&headerSize, 1);

	char buildVersion = 1;
	file.write(&buildVersion, 1);


	char sequenceSize = MinoSequence.size();
	file.write(&sequenceSize, 1);
	for (int i = 0; i < sequenceSize; i++) {
		char mino = MinoSequence[i];
		file.write(&mino, 1);
	}

	uint64_t inputSize = RecordedInput.size();
	file.write((char*)&inputSize, 8);
	for (int i = 0; i < inputSize; i++) {
		char frameSize = RecordedInput[i].size();
		file.write(&frameSize, 1);
		for (int j = 0; j < frameSize; j++) {
			uint32_t button = RecordedInput[i][j];
			file.write((char*)&button, 4);
		}
	}
	
	file.close();
}
Replay::Replay(std::wstring filename) {
	std::fstream file;
	errno = 0;
	file.open(filename, std::ios::in | std::ios::binary);

	if (errno) return;
	char headerSize;
	file.read(&headerSize, 1);

	char header;
	file.read(&header, headerSize);
	//TODO: get header data

	char sequenceSize;
	file.read(&sequenceSize, 1);
	for (int i = 0; i < sequenceSize; i++) {
		char mino;
		file.read(&mino, 1);
		MinoSequence.push_back(mino);
	}

	uint64_t inputSize;
	file.read((char*)&inputSize, 8);
	for (int i = 0; i < inputSize; i++) {
		RecordedInput.push_back({});
		char frameSize;
		file.read(&frameSize, 1);
		for (int j = 0; j < frameSize; j++) {
			uint32_t button;
			file.read((char*)&button, 4);
			auto hejhej = static_cast<InputHandler::ControlButton>(button);
			RecordedInput[i].push_back(hejhej);
		}
	}
	file.close();
}

std::vector<ReplayHeader> Replay::GetReplays() {
	std::vector<ReplayHeader> headers;
	
	std::wstringstream ss;
	PWSTR path = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path)))
	{
		ss << path << "\\Minos\\";
		CreateDirectory(ss.str().c_str(), NULL); // Fails if exists, but no one cares
		ss << "Replays\\";
		CreateDirectory(ss.str().c_str(), NULL); // Fails if exists, but no one cares
	}

	auto dirName = ss.str();
	ss << "*.rpl";
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	//hFind = FindFirstFile(ss.str().c_str(), &ffd);
	hFind = FindFirstFile(ss.str().c_str(), &ffd);
	if (INVALID_HANDLE_VALUE == hFind) {
		auto dwError = GetLastError();
		return headers;
	}
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::wstringstream ss2;
			ss2 << dirName << ffd.cFileName;
			headers.push_back(ss2.str()); // TODO: read header from file instead of just filename
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	return headers;
}