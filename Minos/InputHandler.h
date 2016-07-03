#pragma once

struct Coords {
	int x, y;

	Coords() {};
	Coords(int _x, int _y) : x(_x), y(_y) {};
};

class InputHandler {
public:

	enum ControlButton {
		P1Left = 1,
		P1Right = 2,
		P1RotateLeft = 3,
		P1RotateRight = 4,
		P1SoftDrop = 5,
		P1HardDrop = 6,
		P1SonicDrop = 7,
		P1Hold = 8,

		CloseMenu = 101,
		OpenIngameMenu = 102,
		MenuUp = 103,
		MenuDown = 104,
		SelectMenu = 105
	};
	
	enum MouseButton {
		LeftButton, RightButton
	};

	virtual bool IsHolding(ControlButton button) = 0;
	virtual bool JustPressed(ControlButton button) = 0;

	virtual bool WasMouseButtonClicked(MouseButton button) = 0;
	virtual bool IsMouseButtonHeld(MouseButton button) = 0;
	virtual Coords GetMouseCoords() = 0;

	virtual void BindControl(ControlButton button) = 0;
	virtual void CancelBind() = 0;
	virtual bool IsWaitingForBind(ControlButton button) = 0;
	virtual std::string GetInputFor(ControlButton button) = 0;

	virtual void BeginRecording() = 0;
	virtual void AdvanceFrame() = 0;

	virtual std::vector<std::vector<ControlButton>>& GetRecording() = 0;
};