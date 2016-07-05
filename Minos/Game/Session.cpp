#include "stdafx.h"
#include "../stdafx.h"
#include "Session.h"

Session::Session(GraphicsAdapter* graphics, AudioAdapter* audio, InputHandler* input)
	: _graphics(graphics), _audio(audio), _input(input),
	Well(graphics, audio, input),
	ReplayMenu(graphics, audio, input) {
	
	ReplayMenu.Add(new MenuItem("Quick restart", [this]() -> void {
		Well.Init(new Settings());
	}));
	ReplayMenu.Add(new MenuItem("Watch replay", [this]() -> void {
		auto replay = Well.GetReplay(); // TODO: remember to destroy replay(?)
		Well = GameWell(_graphics, _audio, _input);
		Well.Init(new Settings(), replay);
	}));
	ReplayMenu.Add(new MenuItem("Save replay", [this]() -> void {
		auto replay = Well.GetReplay();
		replay->Save();
		delete replay;
	}));
	ReplayMenu.Add(new MenuItem("Exit", [this]() -> void {}));

};

void Session::Update() {
	Well.Update();

	if (Well.State != GameWell::GameOver) return;

	ReplayMenu.Update();
}
void Session::Draw() {
	Well.Draw();

	if (Well.State != GameWell::GameOver) return;

	ReplayMenu.Draw();
}