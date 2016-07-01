#include "stdafx.h"
#include "../stdafx.h"
#include "ControlConfigMenu.h"

ControlConfigMenu::ControlConfigMenu(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input) : Menu(graphics, audio, input) {

	AddItem("Left", InputHandler::P1Left);
	AddItem("Right", InputHandler::P1Right);
	AddItem("Rotate left", InputHandler::P1RotateLeft);
	AddItem("Rotate right", InputHandler::P1RotateRight);
	AddItem("Soft drop", InputHandler::P1SoftDrop);
	AddItem("Hard drop", InputHandler::P1HardDrop);
	AddItem("Sonic drop", InputHandler::P1SonicDrop);
	AddItem("Hold", InputHandler::P1Hold);
}

void ControlConfigMenu::BeginBinding(InputHandler::ControlButton button, ConfigMenuItem* menuItem) {
	_input->BindControl(button);
	menuItem->SetValue("setting...");

	if (_bindingItem != NULL) {
		_bindingItem->SetValue("");
	}

	_bindingItem = menuItem;
	_bindingButton = button;
}

void ControlConfigMenu::AddItem(std::string name, InputHandler::ControlButton button) {
	ConfigMenuItem* configButton = new ConfigMenuItem(button, name, [&]() -> void { }); // TODO: destruct/clear memory!
	configButton->SetAction([=]() -> void { BeginBinding(button, configButton); });
	AddConfig(button, configButton);
}

void ControlConfigMenu::Update() {
	Menu::Update();

	if (_bindingItem != NULL && !_input->IsWaitingForBind(_bindingButton)) {
		_bindingItem->SetValue(_input->GetInputFor(_bindingButton));
		_bindingItem = NULL;
	}
}