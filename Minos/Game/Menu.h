#pragma once
#include <functional>
#include "../AudioAdapter.h"
#include "../GraphicsAdapter.h"
#include "../InputHandler.h"

class MenuItem {
private:
	std::function<void()> _action;
public:
	std::string Name;
	MenuItem(std::string name, std::function<void()> action) : Name(name), _action(action) { };
	void Select() { _action(); }
};

class Menu {
public:
	Menu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);
	virtual void SelectMenuItem(int index);
	void Update();
	void Draw();
	void Add(MenuItem menuItem) { _menuItems.push_back(menuItem); };

protected:
	std::vector<MenuItem> _menuItems;
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	InputHandler* _input;

private:
	std::vector<int> GetMenuItemPosition(int i);
	int GetHoverMenuItem();
};
