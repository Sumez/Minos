#pragma once

struct Coords {
	int x, y;

	Coords() {};
	Coords(int _x, int _y) : x(_x), y(_y) {};
};

class InputHandler {
public:
	enum MouseButton {
		LeftButton, RightButton
	};

	virtual bool WasMouseButtonClicked(MouseButton button) = 0;
	virtual bool IsMouseButtonHeld(MouseButton button) = 0;
	virtual Coords GetMouseCoords() = 0;
};