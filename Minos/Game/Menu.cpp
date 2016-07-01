#include "stdafx.h"
#include <sstream>
#include "../stdafx.h"
#include "Menu.h"

Menu::Menu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;
}

void Menu::Update() {

	_activeMenuIndex = GetHoverMenuItem();

	if (_input->WasMouseButtonClicked(InputHandler::LeftButton)) {
		if (_activeMenuIndex >= 0) SelectMenuItem(_activeMenuIndex);
	}
}
void Menu::SelectMenuItem(int index) {
	_menuItems[index]->Select();
}
void Menu::Draw() {
	int menuItems = _menuItems.size();

	auto topPos = GetMenuItemPosition(0);
	auto bottomPos = GetMenuItemPosition(3);

	_graphics->DrawRectangle(topPos[0], topPos[1], bottomPos[2], bottomPos[3], 0x000000cc);

	for (int i = 0; i < menuItems; i++){
		auto pos = GetMenuItemPosition(i);
		_graphics->DrawText(_menuItems[i]->Text, pos[0], pos[1], 100, i == _activeMenuIndex ? 0x88ff00ff : 0xffffffff);
	}
}
std::vector<int> Menu::GetMenuItemPosition(int index) {
	// TODO: Proper dynamic positioning of menus etc.

	int x = 100;
	int x2 = 700;
	int y = 100 + index * 120;
	int y2 = 200 + index * 120;

	return{ x, y, x2, y2 };
}
int Menu::GetHoverMenuItem() {
	auto mPos = _input->GetMouseCoords();
	int menuItems = _menuItems.size();
	for (int i = 0; i < menuItems; i++){
		auto pos = GetMenuItemPosition(i);
		if (mPos.x > pos[0] && mPos.x < pos[2] && mPos.y > pos[1] && mPos.y < pos[3]) return i;
	}
	return -1;
}

void ConfigMenuItem::SetValue(std::string value) {
	_value = value;
	std::stringstream ss;
	ss << _name << "! " << value;
	Text = ss.str();
}