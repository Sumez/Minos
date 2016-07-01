#pragma once
#include "Menu.h"

class ControlConfigMenu : public Menu {
public:
	ControlConfigMenu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input);

	void Update();

private:
	void BeginBinding(InputHandler::ControlButton button, ConfigMenuItem* menuItem);
	void AddItem(std::string name, InputHandler::ControlButton button);

	ConfigMenuItem* _bindingItem = NULL;
	InputHandler::ControlButton _bindingButton;
};