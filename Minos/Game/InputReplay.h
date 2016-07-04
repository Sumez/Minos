#pragma once
#include <inttypes.h>
#include "../InputHandler.h"

class InputReplay : public InputHandler {
public:

	InputReplay(std::vector<std::vector<ControlButton>>& recording);

	virtual Coords GetMouseCoords();
	virtual bool IsHolding(ControlButton button);
	virtual bool JustPressed(ControlButton button);
	virtual bool WasMouseButtonClicked(MouseButton button);
	virtual bool IsMouseButtonHeld(MouseButton button);
	virtual void BindControl(ControlButton button);
	virtual void CancelBind();
	virtual bool IsWaitingForBind(ControlButton button) { return false; }
	virtual std::string GetInputFor(ControlButton button);
	virtual void AdvanceFrame();
	virtual void BeginRecording();
	virtual std::vector<std::vector<ControlButton>>& GetRecording() { return _recording; };

private:

	uint64_t _frame = 0;
	std::vector<std::vector<ControlButton>>& _recording;
}; 