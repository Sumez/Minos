#include "stdafx.h"
#include "../stdafx.h"
#include "OldSchoolSettings.h"


int OldSchoolSettings::AreDelay(int row) {
	if (row <= 3) return 20;
	else if (row <= 7) return 18;
	else if (row <= 11) return 16;
	else if (row <= 15) return 14;
	else if (row <= 19) return 12;
	else return 10;
}

int OldSchoolSettings::GetDropScore(int droppedDistance) {
	return droppedDistance;
}
int OldSchoolSettings::GetLineClearScore(int linesCleared) {
	int base = linesCleared == 4 ? 1200 :
		linesCleared == 3 ? 300 :
		linesCleared == 2 ? 100 : 40;
	return base * (_level + 1);
}

void OldSchoolSettings::SetLevel(int level) {

	_level = level;
	if (_level < 9) _gravity = 60 / (8 + ((8 - _level) * 5));
	else if (_level < 10) _gravity = 10;
	else if (_level < 13) _gravity = 12;
	else if (_level < 16) _gravity = 15;
	else if (_level < 19) _gravity = 20;
	else if (_level < 29) _gravity = 30;
	else _gravity = 60;
}