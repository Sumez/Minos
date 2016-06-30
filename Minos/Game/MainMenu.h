#pragma once
#include "Menu.h"
#include <functional>

class MainMenu : public Menu {
public:
	MainMenu(GraphicsAdapter* graphics, AudioAdapter* audio);

	virtual void SelectMenuItem(int index);
	std::function<void()> StartNewGame;
};