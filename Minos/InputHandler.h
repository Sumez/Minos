#pragma once
#include "Game/Coords.h"

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

	virtual std::vector<int>& GetRecording() = 0;

protected:
	std::map<ControlButton, bool> _isPressed;
	std::vector<ControlButton> _justPressed;

	void PressedButton(ControlButton button)  {
		if (!_isPressed.count(button) || !_isPressed[button]) _justPressed.push_back(button);
		_isPressed[button] = true;
	};
	void ReleasedButton(ControlButton button)  {
		_isPressed[button] = false;
	};
};