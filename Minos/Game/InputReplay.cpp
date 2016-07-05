#include "stdafx.h"
#include "../stdafx.h"
#include "InputReplay.h"

InputReplay::InputReplay(std::vector<int>& recording) : _recording(recording) {
}

Coords InputReplay::GetMouseCoords() { return Coords(); }
bool InputReplay::IsHolding(ControlButton button) {
	return _isPressed.count(button) && _isPressed[button];
}
bool InputReplay::JustPressed(ControlButton button) {
	return std::find(_justPressed.begin(), _justPressed.end(), button) != _justPressed.end();
}
bool InputReplay::WasMouseButtonClicked(MouseButton button) {
	return false;
}
bool InputReplay::IsMouseButtonHeld(MouseButton button) {
	return false;
}
void InputReplay::BindControl(ControlButton button) { }
void InputReplay::CancelBind() { }
std::string InputReplay::GetInputFor(ControlButton button) { return ""; }
void InputReplay::AdvanceFrame() {
	_frame++;
	ProcessInput();
}
void InputReplay::BeginRecording() {
	_frame = 0;
	_pointer = 0;
	ProcessInput();
}
void InputReplay::ProcessInput() {
	if (_recording.size() <= _pointer) return;
	int inputs = _recording[_pointer];
	_pointer++;

	for (int i = 0; i < inputs; i++) {
		if (_recording[_pointer] > 0) PressedButton(static_cast<ControlButton>(_recording[_pointer]));
		else ReleasedButton(static_cast<ControlButton>(- _recording[_pointer]));
		++_pointer;
	}
}