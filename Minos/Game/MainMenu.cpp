#include "stdafx.h"
#include "../stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu(GraphicsAdapter* graphics, AudioAdapter* audio) : Menu(graphics, audio) {

	_menuItems.push_back(MenuItem("Begin game"));
	_menuItems.push_back(MenuItem("Configuration"));
	_menuItems.push_back(MenuItem("Exit"));
}

void MainMenu::SelectMenuItem(int index) {
	if (index == 0) StartNewGame();
}