#pragma once
#include "Mino.h"

class Settings {
public:

	enum ResetType {
		None = 0x00,
		StepReset = 0x01,
		MoveReset = 0x02,
		RotateReset = 0x04
	};

	void SetLevel(int level);

	MinoColors GetPieceColor(Mino::MinoType type);
	bool LevelOnSpawn() { return true; };
	int MaxLevel() { return 999; };
	int LockDelay() { return _lockDelay; };
	int Gravity() { return _gravity; }; // 5120;
	int GravityResolution() { return 256; };
	int AreDelay(int row) { return _are; };
	int AreDelayOnLineClear(int row) { return _lineAre; };
	int LineClearDelay() { return _lineClearDelay; }; // TODO: 0 = next frame, right now the first frame seems to be skipped? Probably true for other delays as well
	int GetDropScore(int droppedDistance);
	int GetLineClearScore(int linesCleared);
	int DasCharge() { return _dasCharge; };
	int DasRepeat() { return 1; };
	ResetType LockReset();
	bool Irs() { return true; };


	//TODO: RNG settings
	//TODO: Define rotation system (ARS/SRS/NES/??) + wallkicks

	//not implemented yet:
	int GarbageHeight() { return 0; };
	int MaxGhostLevel() { return 99; };
private:
	int _level;
	int _are;
	int _lineAre;
	int _lockDelay;
	int _lineClearDelay;
	int _dasCharge;

	int _gravity;
};