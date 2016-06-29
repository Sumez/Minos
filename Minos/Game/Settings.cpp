#include "stdafx.h"
#include "Settings.h"

MinoColors Settings::GetPieceColor(Mino::MinoType type) {
	switch (type) {
	case Mino::MinoType::S: return MinoColors::Purple;
	case Mino::MinoType::O: return MinoColors::Yellow;
	case Mino::MinoType::J: return MinoColors::Blue;
	case Mino::MinoType::L: return MinoColors::Orange;
	case Mino::MinoType::Z: return MinoColors::Green;
	case Mino::MinoType::I: return MinoColors::Red;
	case Mino::MinoType::T: return MinoColors::Cyan;
	default: return MinoColors::Gray;
	}
}

int Settings::GetDropScore(int droppedDistance) {
	return droppedDistance;
}
int Settings::GetLineClearScore(int linesCleared) {
	int base = linesCleared == 4 ? 1200 :
		linesCleared == 3 ? 300 :
		linesCleared == 2 ? 100 : 40;
	return base * (_level + 1);
}

void Settings::SetLevel(int level) {
	_level = level;

	if (level >= 500) _gravity = 5120;
	else if (level >= 450) _gravity = 768;
	else if (level >= 420) _gravity = 1024;
	else if (level >= 400) _gravity = 1280;
	else if (level >= 360) _gravity = 1024;
	else if (level >= 330) _gravity = 768;
	else if (level >= 300) _gravity = 512;
	else if (level >= 251) _gravity = 256;
	else if (level >= 247) _gravity = 224;
	else if (level >= 243) _gravity = 192;
	else if (level >= 239) _gravity = 160;
	else if (level >= 236) _gravity = 128;
	else if (level >= 233) _gravity = 96;
	else if (level >= 230) _gravity = 64;
	else if (level >= 220) _gravity = 32;
	else if (level >= 200) _gravity = 4;
	else if (level >= 170) _gravity = 144;
	else if (level >= 160) _gravity = 128;
	else if (level >= 140) _gravity = 112;
	else if (level >= 120) _gravity = 96;
	else if (level >= 100) _gravity = 80;
	else if (level >= 90) _gravity = 64;
	else if (level >= 80) _gravity = 48;
	else if (level >= 70) _gravity = 32;
	else if (level >= 60) _gravity = 16;
	else if (level >= 50) _gravity = 12;
	else if (level >= 40) _gravity = 10;
	else if (level >= 35) _gravity = 8;
	else if (level >= 30) _gravity = 6;
	else if (level >= 0) _gravity = 4;
	else _gravity = 0;
	_are = _lineAre = 25;
	if (level >= 801) _are = 12;
	else if (level >= 701) _are = 16;
	else if (level >= 601) _are = 25;
	if (level >= 801) _lineAre = 6;
	else if (level >= 701) _lineAre = 12;
	else if (level >= 601) _lineAre = 16;

	_lockDelay = level >= 901 ? 17 : 30;	if (level >= 801) _lineClearDelay = 6;
	else if(level >= 701) _lineClearDelay = 12;
	else if(level >= 601) _lineClearDelay = 16;
	else if(level >= 500) _lineClearDelay = 25;
	else _lineClearDelay = 40;

	if (level >= 900) _dasCharge = 6;
	else if (level >= 500) _dasCharge = 8;
	else _dasCharge = 14;
}
Settings::ResetType Settings::LockReset() {
	return static_cast<ResetType>(StepReset);
};