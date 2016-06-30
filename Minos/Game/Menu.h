#pragma once
#include "../AudioAdapter.h"
#include "../GraphicsAdapter.h"

class MenuItem {
public:
	MenuItem(std::string name) { Name = name; };
	std::string Name;
	void Select() {};
};

class Menu {
public:
	Menu(GraphicsAdapter* graphics, AudioAdapter* audio);
	virtual void SelectMenuItem(int index);
	void Update();
	void Draw();

protected:
	std::vector<MenuItem> _menuItems;
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;

private:
	std::vector<int> GetMenuItemPosition(int i);
	int GetHoverMenuItem();
};
