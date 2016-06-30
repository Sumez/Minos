#include "stdafx.h"
#include "../stdafx.h"
#include "Menu.h"

Menu::Menu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) {
	_graphics = graphics;
	_audio = audio;
	_input = input;
}

void Menu::Update() {


	if (_input->WasMouseButtonClicked(InputHandler::LeftButton)) {

		int hoverMenu = GetHoverMenuItem();
		if (hoverMenu >= 0) SelectMenuItem(hoverMenu);

	}
}
void Menu::SelectMenuItem(int index) {
	_menuItems[index].Select();
}
void Menu::Draw() {
	int hoverMenu = GetHoverMenuItem();

	int menuItems = _menuItems.size();
	for (int i = 0; i < menuItems; i++){
		auto pos = GetMenuItemPosition(i);
		_graphics->DrawText(_menuItems[i].Name, pos[0], pos[1], 100, i == hoverMenu ? 0x88ff00ff : 0xffffffff);
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