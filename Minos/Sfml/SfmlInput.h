#pragma once
#include "../InputHandler.h"

class SfmlInput : public InputHandler {
public:

	virtual Coords GetMouseCoords();
	virtual bool WasMouseButtonClicked(MouseButton button);
	virtual bool IsMouseButtonHeld(MouseButton button);

	void PressedKey(int key);
	void ReleasedKey(int key);
	void PressedJoystickButton(int stickId, int key);
	void ReleasedJoystickButton(int stickId, int key);
	void ClickedMouse(int key);
	void UnclickedMouse(int key);
	void Clear();

	void MovedMouse(sf::Vector2f coords);

private:
	std::map<int, bool> _isPressed;
	std::vector<int> _justPressed;

	std::map<int, bool> _isClicked;
	std::vector<int> _justClicked;

	sf::Vector2f _mouseCoords;
};