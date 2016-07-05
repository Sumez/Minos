#pragma once
#include "Mino.h"
#include "Coords.h"

class Settings {
public:

	enum Preset {
		Custom = 0,
		Master = 1,
		OldSchool = 2,
		Modern = 3,
		Guide = 4,
		Death = 5
	};

	enum ResetType {
		None = 0x00,
		StepReset = 0x01,
		MoveReset = 0x02,
		RotateReset = 0x04
	};

	static Settings* GetPreset(Preset preset);

	virtual void SetLevel(int level);

	virtual Coords GridSize() { return Coords(10, 22); };
	virtual int InvisibleRows() { return 2; };
	virtual MinoColors GetPieceColor(Mino::MinoType type);
	virtual bool LevelOnSpawn() { return true; };
	virtual int MaxLevel() { return 999; };
	virtual int LockDelay() { return _lockDelay; };
	virtual int Gravity() { return _gravity; }; // 5120;
	virtual int GravityResolution() { return 256; };
	virtual int AreDelay(int row) { return _are; };
	virtual int AreDelayOnLineClear(int row) { return _lineAre; };
	virtual int LineClearDelay() { return _lineClearDelay; }; // TODO: 0 = next frame, right now the first frame seems to be skipped? Probably true for other delays as well
	virtual int GetDropScore(int droppedDistance);
	virtual int GetLineClearScore(int linesCleared);
	virtual int DasCharge() { return _dasCharge; };
	virtual int DasRepeat() { return 1; };
	virtual ResetType LockReset();
	virtual bool Irs() { return true; };


	//TODO: RNG settings
	//TODO: Define rotation system (ARS/SRS/NES/??) + wallkicks

	//not implemented yet:
	virtual bool LinesPerLevel() { return 1; };
	virtual int GarbageHeight() { return 0; };
	virtual int MaxGhostLevel() { return 99; };
protected:
	int _level;
	int _are;
	int _lineAre;
	int _lockDelay;
	int _lineClearDelay;
	int _dasCharge;

	int _gravity;
};