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