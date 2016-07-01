#pragma once

struct Coords {
	int x, y;

	Coords() {};
	Coords(int _x, int _y) : x(_x), y(_y) {};
};

class InputHandler {
public:

	enum ControlButton {
		P1Left, P1Right, P1RotateLeft, P1RotateRight, P1SoftDrop, P1HardDrop, P1SonicDrop, P1Hold
	};

	enum MouseButton {
		LeftButton, RightButton
	};

	virtual bool IsHolding(ControlButton button) = 0;

	virtual bool WasMouseButtonClicked(MouseButton button) = 0;
	virtual bool IsMouseButtonHeld(MouseButton button) = 0;
	virtual Coords GetMouseCoords() = 0;

	virtual void BindControl(ControlButton button) = 0;
	virtual void CancelBind() = 0;
	virtual bool IsWaitingForBind(ControlButton button) = 0;
	virtual std::string GetInputFor(ControlButton button) = 0;
};