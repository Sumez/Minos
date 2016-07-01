#pragma once
#include "../InputHandler.h"

class SfmlInput : public InputHandler {
public:

	virtual Coords GetMouseCoords();
	virtual bool WasMouseButtonClicked(MouseButton button);
	virtual bool IsMouseButtonHeld(MouseButton button);
	virtual void BindControl(ControlButton button);
	virtual void CancelBind() { _binding = false; }
	virtual bool IsWaitingForBind(ControlButton button) { return _binding; } // TODO
	virtual std::string GetInputFor(ControlButton button);

	void PressedKey(int key);
	void ReleasedKey(int key);
	void PressedJoystickButton(int stickId, int key);
	void ReleasedJoystickButton(int stickId, int key);
	void ClickedMouse(int key);
	void UnclickedMouse(int key);
	void Clear();

	void MovedMouse(sf::Vector2f coords);

private:

	bool _binding = false;
	ControlButton _bindingControl;

	std::map<int, ControlButton> _mappings;
	std::map<ControlButton, int> _reverseMappings;


	std::map<int, bool> _isPressed;
	std::vector<int> _justPressed;

	std::map<int, bool> _isClicked;
	std::vector<int> _justClicked;

	sf::Vector2f _mouseCoords;
};