#pragma once
#include "Settings.h"

class OldSchoolSettings : public Settings {

public:

	virtual void SetLevel(int level);

	virtual bool LevelOnSpawn() { return false; };
	virtual int MaxLevel() { return 999; };
	virtual int LockDelay() { return 0; };
	virtual int GravityResolution() { return 60; };
	virtual int AreDelay(int row);
	virtual int AreDelayOnLineClear(int row) { return AreDelay(row); };
	virtual int LineClearDelay() { return 20; };
	virtual int GetDropScore(int droppedDistance);
	virtual int GetLineClearScore(int linesCleared);
	virtual int DasCharge() { return 16; };
	virtual int DasRepeat() { return 6; };
	virtual ResetType LockReset() { return ResetType::None; }
	virtual bool Irs() { return false; };


	//TODO: RNG settings
	//TODO: Define rotation system (ARS/SRS/NES/??) + wallkicks

	//not implemented yet:
	virtual bool LinesPerLevel() { return 10; };
	virtual int GarbageHeight() { return 0; };
	virtual int MaxGhostLevel() { return 99; };


};