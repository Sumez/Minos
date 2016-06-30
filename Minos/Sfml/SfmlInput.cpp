#include "stdafx.h"
#include "../stdafx.h"
#include "SfmlInput.h"

void SfmlInput::PressedKey(int key) {
	if (!_isPressed.count(key)) _justPressed.push_back(key);
	_isPressed[key] = true;
}
void SfmlInput::ReleasedKey(int key) {
	_isPressed[key] = false;
}
void SfmlInput::PressedJoystickButton(int stickId, int key) {
}
void SfmlInput::ReleasedJoystickButton(int stickId, int key) {

}
void SfmlInput::ClickedMouse(int key) {
	if (!_isClicked.count(key)) _justClicked.push_back(key);
	_isClicked[key] = true;
}
void SfmlInput::UnclickedMouse(int key) {
	_isPressed[key] = false;
}
void SfmlInput::Clear() {
	_justPressed.clear();
	_justClicked.clear();
}
void SfmlInput::MovedMouse(sf::Vector2f coords) {
	_mouseCoords = coords;
}

Coords SfmlInput::GetMouseCoords() {
	return Coords(_mouseCoords.x, _mouseCoords.y);
}
bool SfmlInput::WasMouseButtonClicked(MouseButton button) {
	return std::find(_justClicked.begin(), _justClicked.end(), button == LeftButton ? 0 : button == RightButton ? 1 : 2) != _justClicked.end();
}
bool SfmlInput::IsMouseButtonHeld(MouseButton button) {
	return false;
}