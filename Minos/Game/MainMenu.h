#pragma once
#include "Menu.h"

class MainMenu : public Menu {
public:
	MainMenu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);
};