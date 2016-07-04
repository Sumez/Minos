#include "stdafx.h"
#include "../stdafx.h"
#include "InputReplay.h"

InputReplay::InputReplay(std::vector<std::vector<ControlButton>>& recording) : _recording(recording) {
}

Coords InputReplay::GetMouseCoords() { return Coords(); }
bool InputReplay::IsHolding(ControlButton button) {
	if (_frame >= _recording.size()) return false;
	std::vector<ControlButton>& heldButtons = _recording[_frame];
	return std::find(heldButtons.begin(), heldButtons.end(), button) != heldButtons.end();
}
bool InputReplay::JustPressed(ControlButton button) {
	return false;
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
}
void InputReplay::BeginRecording() {
	_frame = 0;
}