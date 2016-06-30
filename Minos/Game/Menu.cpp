#include "stdafx.h"
#include "../stdafx.h"
#include "Menu.h"

Menu::Menu(GraphicsAdapter* graphics, AudioAdapter* audio) {
	_graphics = graphics;
	_audio = audio;
}

void Menu::Update() {


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

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
	auto mPos = _graphics->GetMousePosition();
	int menuItems = _menuItems.size();
	for (int i = 0; i < menuItems; i++){
		auto pos = GetMenuItemPosition(i);
		if (mPos[0] > pos[0] && mPos[0] < pos[2] && mPos[1] > pos[1] && mPos[1] < pos[3]) return i;
	}
	return -1;
}