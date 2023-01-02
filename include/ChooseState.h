#pragma once
#include "Music.h"
#include "State.h"
class ChooseState : public State {
public:
	ChooseState();
	~ChooseState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	Music backgroundMusic;
};
