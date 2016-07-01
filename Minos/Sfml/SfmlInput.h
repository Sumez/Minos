#pragma once
#include <inttypes.h>
#include "../InputHandler.h"

class SfmlInput : public InputHandler {
public:

	virtual Coords GetMouseCoords();
	virtual bool IsHolding(ControlButton button);
	virtual bool WasMouseButtonClicked(MouseButton button);
	virtual bool IsMouseButtonHeld(MouseButton button);
	virtual void BindControl(ControlButton button);
	virtual void CancelBind() { _binding = false; }
	virtual bool IsWaitingForBind(ControlButton button) { return _binding; } // TODO
	virtual std::string GetInputFor(ControlButton button);

	void Load();
	void PressedKey(uint32_t key);
	void ReleasedKey(uint32_t key);
	void PressedJoystickButton(uint32_t stickId, uint32_t key);
	void ReleasedJoystickButton(uint32_t stickId, uint32_t key);
	void MovedJoystick(uint32_t stickId, sf::Joystick::Axis axis, float amount);
	void ClickedMouse(int key);
	void UnclickedMouse(int key);
	void Clear();

	void MovedMouse(sf::Vector2f coords);

private:

	void PressedKeyId(uint64_t keyId);
	void ReleasedKeyId(uint64_t keyId);

	bool _binding = false;
	ControlButton _bindingControl;

	std::map<uint64_t, ControlButton> _mappings;
	std::map<ControlButton, uint64_t> _reverseMappings;


	std::map<uint64_t, bool> _isPressed;
	std::vector<uint64_t> _justPressed;

	std::map<int, bool> _isClicked;
	std::vector<int> _justClicked;

	sf::Vector2f _mouseCoords;
};