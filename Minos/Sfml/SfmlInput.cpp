#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "../stdafx.h"
#include "SfmlInput.h"
#include <ShlObj.h>
#include <Windows.h>

std::wstring ConfigFile() {
	std::wstringstream ss;
	TCHAR path[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, path)))
	{
		// Append product-specific path
		//PathAppend(path, _T("\\My Company\\My Product\\1.0\\"));
		ss << path << "\\Minos\\";
		CreateDirectory(ss.str().c_str(), NULL);
	}
	ss << "settings.cfg";
	return ss.str();
}

void SaveSettings(std::map<InputHandler::ControlButton, std::vector<uint64_t>> map) {
	std::ofstream file;
	errno = 0;
	file.open(ConfigFile(), std::ios::out | std::ios::trunc | std::ios::binary);
	if (errno) return;
	char mapSize = map.size();
	file.write(&mapSize, 1);
	for (auto const &mapping : map) {
		uint32_t button = mapping.first;
		auto keys = mapping.second;
		int keysSize = keys.size();
		for (int i = 0; i < keysSize; i++) {
			uint64_t keyId = keys[i];
			file.write((char*)&button, 4);
			file.write((char*)&keyId, 8);
		}
	}
	for (int i = 0; i < mapSize; i++) {
		;
	}
	file.close();
}
std::map<InputHandler::ControlButton, std::vector<uint64_t>> LoadSettings() {
	std::map<InputHandler::ControlButton, std::vector<uint64_t>> map;
	std::fstream file;
	errno = 0;
	file.open(ConfigFile(), std::ios::in | std::ios::binary);
	if (errno) return map;
	char mapSize = map.size();
	file.read(&mapSize, 1);
	for (int i = 0; i < mapSize; i++) {
		//InputHandler::ControlButton> button
		uint32_t button;
		uint64_t keyId;
		file.read((char*)&button, 4);
		file.read((char*)&keyId, 8);

		auto hejhej = static_cast<InputHandler::ControlButton>(button);
		if (!map.count(hejhej)) map[hejhej] = std::vector<uint64_t>();
		map[hejhej].push_back(keyId);
	}
	file.close();
	return map;
}
std::string getJoystickButtonName(int joystickIndex, int button) {
	std::stringstream ss;
	ss << "Joystick" << std::to_string(joystickIndex + 1) << " ";

	if (button == 101) ss << "Left";
	else if (button == 102) ss << "Right";
	else if (button == 103) ss << "Down";
	else if (button == 104) ss << "Up";
	else ss << "Button" << std::to_string(button);

	return ss.str();
}
std::string getKeyName(const sf::Keyboard::Key key) {
	switch (key) {
	default:
	case sf::Keyboard::Unknown:
		return "Unknown";
	case sf::Keyboard::A:
		return "A";
	case sf::Keyboard::B:
		return "B";
	case sf::Keyboard::C:
		return "C";
	case sf::Keyboard::D:
		return "D";
	case sf::Keyboard::E:
		return "E";
	case sf::Keyboard::F:
		return "F";
	case sf::Keyboard::G:
		return "G";
	case sf::Keyboard::H:
		return "H";
	case sf::Keyboard::I:
		return "I";
	case sf::Keyboard::J:
		return "J";
	case sf::Keyboard::K:
		return "K";
	case sf::Keyboard::L:
		return "L";
	case sf::Keyboard::M:
		return "M";
	case sf::Keyboard::N:
		return "N";
	case sf::Keyboard::O:
		return "O";
	case sf::Keyboard::P:
		return "P";
	case sf::Keyboard::Q:
		return "Q";
	case sf::Keyboard::R:
		return "R";
	case sf::Keyboard::S:
		return "S";
	case sf::Keyboard::T:
		return "T";
	case sf::Keyboard::U:
		return "U";
	case sf::Keyboard::V:
		return "V";
	case sf::Keyboard::W:
		return "W";
	case sf::Keyboard::X:
		return "X";
	case sf::Keyboard::Y:
		return "Y";
	case sf::Keyboard::Z:
		return "Z";
	case sf::Keyboard::Num0:
		return "Num0";
	case sf::Keyboard::Num1:
		return "Num1";
	case sf::Keyboard::Num2:
		return "Num2";
	case sf::Keyboard::Num3:
		return "Num3";
	case sf::Keyboard::Num4:
		return "Num4";
	case sf::Keyboard::Num5:
		return "Num5";
	case sf::Keyboard::Num6:
		return "Num6";
	case sf::Keyboard::Num7:
		return "Num7";
	case sf::Keyboard::Num8:
		return "Num8";
	case sf::Keyboard::Num9:
		return "Num9";
	case sf::Keyboard::Escape:
		return "Escape";
	case sf::Keyboard::LControl:
		return "LControl";
	case sf::Keyboard::LShift:
		return "LShift";
	case sf::Keyboard::LAlt:
		return "LAlt";
	case sf::Keyboard::LSystem:
		return "LSystem";
	case sf::Keyboard::RControl:
		return "RControl";
	case sf::Keyboard::RShift:
		return "RShift";
	case sf::Keyboard::RAlt:
		return "RAlt";
	case sf::Keyboard::RSystem:
		return "RSystem";
	case sf::Keyboard::Menu:
		return "Menu";
	case sf::Keyboard::LBracket:
		return "LBracket";
	case sf::Keyboard::RBracket:
		return "RBracket";
	case sf::Keyboard::SemiColon:
		return "SemiColon";
	case sf::Keyboard::Comma:
		return "Comma";
	case sf::Keyboard::Period:
		return "Period";
	case sf::Keyboard::Quote:
		return "Quote";
	case sf::Keyboard::Slash:
		return "Slash";
	case sf::Keyboard::BackSlash:
		return "BackSlash";
	case sf::Keyboard::Tilde:
		return "Tilde";
	case sf::Keyboard::Equal:
		return "Equal";
	case sf::Keyboard::Dash:
		return "Dash";
	case sf::Keyboard::Space:
		return "Space";
	case sf::Keyboard::Return:
		return "Return";
	case sf::Keyboard::BackSpace:
		return "BackSpace";
	case sf::Keyboard::Tab:
		return "Tab";
	case sf::Keyboard::PageUp:
		return "PageUp";
	case sf::Keyboard::PageDown:
		return "PageDown";
	case sf::Keyboard::End:
		return "End";
	case sf::Keyboard::Home:
		return "Home";
	case sf::Keyboard::Insert:
		return "Insert";
	case sf::Keyboard::Delete:
		return "Delete";
	case sf::Keyboard::Add:
		return "Add";
	case sf::Keyboard::Subtract:
		return "Subtract";
	case sf::Keyboard::Multiply:
		return "Multiply";
	case sf::Keyboard::Divide:
		return "Divide";
	case sf::Keyboard::Left:
		return "Left";
	case sf::Keyboard::Right:
		return "Right";
	case sf::Keyboard::Up:
		return "Up";
	case sf::Keyboard::Down:
		return "Down";
	case sf::Keyboard::Numpad0:
		return "Numpad0";
	case sf::Keyboard::Numpad1:
		return "Numpad1";
	case sf::Keyboard::Numpad2:
		return "Numpad2";
	case sf::Keyboard::Numpad3:
		return "Numpad3";
	case sf::Keyboard::Numpad4:
		return "Numpad4";
	case sf::Keyboard::Numpad5:
		return "Numpad5";
	case sf::Keyboard::Numpad6:
		return "Numpad6";
	case sf::Keyboard::Numpad7:
		return "Numpad7";
	case sf::Keyboard::Numpad8:
		return "Numpad8";
	case sf::Keyboard::Numpad9:
		return "Numpad9";
	case sf::Keyboard::F1:
		return "F1";
	case sf::Keyboard::F2:
		return "F2";
	case sf::Keyboard::F3:
		return "F3";
	case sf::Keyboard::F4:
		return "F4";
	case sf::Keyboard::F5:
		return "F5";
	case sf::Keyboard::F6:
		return "F6";
	case sf::Keyboard::F7:
		return "F7";
	case sf::Keyboard::F8:
		return "F8";
	case sf::Keyboard::F9:
		return "F9";
	case sf::Keyboard::F10:
		return "F10";
	case sf::Keyboard::F11:
		return "F11";
	case sf::Keyboard::F12:
		return "F12";
	case sf::Keyboard::F13:
		return "F13";
	case sf::Keyboard::F14:
		return "F14";
	case sf::Keyboard::F15:
		return "F15";
	case sf::Keyboard::Pause:
		return "Pause";
	}
}

uint64_t combine64(uint32_t i1, uint32_t i2) {
	return (uint64_t)i1 << 32 | i2;
}
std::vector<uint32_t> split64(uint64_t i) {
	return{ (uint32_t)(i >> 32), (uint32_t)i };
}

void SfmlInput::Load() {
	//TODO: If load fails (default controls)
	_reverseMappings = LoadSettings();

	_reverseMappings[ControlButton::CloseMenu] = { combine64(100, sf::Keyboard::Escape) };
	_reverseMappings[ControlButton::OpenIngameMenu] = { combine64(100, sf::Keyboard::Escape) };
	_reverseMappings[ControlButton::MenuUp] = { combine64(100, sf::Keyboard::Up) };
	_reverseMappings[ControlButton::MenuDown] = { combine64(100, sf::Keyboard::Down) };
	_reverseMappings[ControlButton::SelectMenu] = { combine64(100, sf::Keyboard::Return) };

	_mappings.clear();
	for (auto const &mapping : _reverseMappings) {
		uint32_t button = mapping.first;
		auto keys = mapping.second;
		int keysSize = keys.size();
		auto hejhej = static_cast<InputHandler::ControlButton>(button);
		for (int i = 0; i < keysSize; i++) {
			if (!_mappings.count(keys[i])) _mappings[keys[i]] = std::vector<ControlButton>();
			_mappings[keys[i]].push_back(hejhej);
		}
	}

}
void SfmlInput::PressedKeyId(uint64_t keyId) {
	if (_binding) {
		if (!_mappings.count(keyId)) _mappings[keyId] = {};
		if (!_reverseMappings.count(_bindingControl)) _mappings[_bindingControl] = {};
		_mappings[keyId].push_back(_bindingControl);
		_reverseMappings[_bindingControl].push_back(keyId);
		_binding = false;

		SaveSettings(_reverseMappings);
	}

	if (!_mappings.count(keyId)) return;
	auto buttons = _mappings[keyId];
	int buttonsSize = buttons.size();
	for (int i = 0; i < buttonsSize; i++) {
		if (!_isPressed.count(buttons[i]) || !_isPressed[buttons[i]]) _justPressed.push_back(buttons[i]);
		_isPressed[buttons[i]] = true;
	}
}
void SfmlInput::ReleasedKeyId(uint64_t keyId) {
	if (!_mappings.count(keyId)) return;
	auto buttons = _mappings[keyId];
	int buttonsSize = buttons.size();
	for (int i = 0; i < buttonsSize; i++) {
		_isPressed[buttons[i]] = false;
	}
}
void SfmlInput::PressedKey(uint32_t key) {
	PressedKeyId(combine64(100, key));
}
void SfmlInput::ReleasedKey(uint32_t key) {
	ReleasedKeyId(combine64(100, key));
}
void SfmlInput::MovedJoystick(uint32_t stickId, sf::Joystick::Axis axis, float amount) {
	if (amount <= -100 && axis == sf::Joystick::PovX)
		PressedJoystickButton(stickId, 101);
	if (amount >= 100 && axis == sf::Joystick::PovX)
		PressedJoystickButton(stickId, 102);
	if (amount <= -100 && axis == sf::Joystick::PovY)
		PressedJoystickButton(stickId, 103);
	if (amount >= 100 && axis == sf::Joystick::PovY)
		PressedJoystickButton(stickId, 104);

	if (amount > -100 && axis == sf::Joystick::PovX)
		ReleasedJoystickButton(stickId, 101);
	if (amount < 100 && axis == sf::Joystick::PovX)
		ReleasedJoystickButton(stickId, 102);
	if (amount > -100 && axis == sf::Joystick::PovY)
		ReleasedJoystickButton(stickId, 103);
	if (amount < 100 && axis == sf::Joystick::PovY)
		ReleasedJoystickButton(stickId, 104);
}
void SfmlInput::PressedJoystickButton(uint32_t stickId, uint32_t button) {
	PressedKeyId(combine64(stickId, button));
}
void SfmlInput::ReleasedJoystickButton(uint32_t stickId, uint32_t button) {
	ReleasedKeyId(combine64(stickId, button));
}
void SfmlInput::ClickedMouse(int key) {
	if (!_isClicked.count(key) || !_isClicked[key]) _justClicked.push_back(key);
	_isClicked[key] = true;
}
void SfmlInput::UnclickedMouse(int key) {
	_isClicked[key] = false;
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
bool SfmlInput::IsHolding(ControlButton button) {
	return _isPressed.count(button) && _isPressed[button];
}
bool SfmlInput::JustPressed(ControlButton button) {;
	return std::find(_justPressed.begin(), _justPressed.end(), button) != _justPressed.end();
}
bool SfmlInput::IsMouseButtonHeld(MouseButton button) {
	return _isClicked.count(button) && _isClicked[button];
}
std::string SfmlInput::GetInputFor(ControlButton button) {
	auto inputIndex = split64(_reverseMappings[button][0]);
	return inputIndex[0] == 100 ? getKeyName(static_cast<sf::Keyboard::Key>(inputIndex[1]))
		: getJoystickButtonName(inputIndex[0], inputIndex[1]);
}

void SfmlInput::BindControl(ControlButton button) {
	_binding = true;
	_bindingControl = button;
}

void SfmlInput::AdvanceFrame() {
	std::vector<ControlButton> frameData;
	for (auto const &mapping : _isPressed) {
		if (mapping.second) frameData.push_back(mapping.first);
	}
	_recording.push_back(frameData);
}
void SfmlInput::BeginRecording() {
	_recording.clear();
}