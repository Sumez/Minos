#pragma once
#include <functional>
#include "../AudioAdapter.h"
#include "../GraphicsAdapter.h"
#include "../InputHandler.h"

class MenuItem {
private:
	std::function<void()> _action;
public:
	std::string Text;
	MenuItem(std::string name, std::function<void()> action) : Text(name), _action(action) { };
	void Select() { _action(); }
	void SetAction(std::function<void()> action) { _action = action; };
};
class ConfigMenuItem : public MenuItem {
private:
	std::string _name;
	std::string _value;
public: 
	int Id;
	void SetValue(std::string value);
	ConfigMenuItem(int id, std::string name, std::function<void()> action, std::string value = "") : MenuItem(name, action), Id(id), _name(name) { SetValue(value); };
};

class Menu {
public:
	Menu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);
	virtual void SelectMenuItem(int index);
	virtual void Update();
	virtual void Draw();
	virtual void Add(MenuItem* menuItem) { _menuItems.push_back(menuItem); };
	virtual void AddConfig(int id, ConfigMenuItem* menuItem) { Add(menuItem); _configItems.push_back(menuItem); };

protected:
	std::vector<MenuItem*> _menuItems;
	std::vector<ConfigMenuItem*> _configItems;
	GraphicsAdapter* _graphics;
	AudioAdapter* _audio;
	InputHandler* _input;

private:
	std::vector<int> GetMenuItemPosition(int i);
	int GetHoverMenuItem();

	int _selectedMenuIndex = 0;
	int _activeMenuIndex = 0;
};
