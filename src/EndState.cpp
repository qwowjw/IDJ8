#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState2.h"
#include "TitleState.h"

EndState::EndState() {
	quitRequested = false;
	if ((GameData::playerVictory == true)&& (GameData::fase2 == true)) {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/win.jpg");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = Music("assets/audio/acabou.mp3");
		backgroundMusic.Play();
	}
	else if ((GameData::playerVictory == true)&& (GameData::fase2 == false)) {
		Game::GetInstance().Push(new StageState2());
	}
	else {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/lose.jpg");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = Music("assets/audio/among.mp3");
		backgroundMusic.Play();
	}
}

void EndState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		popRequested = true;
	}
}

void EndState::Render() {
	RenderArray();
}

void EndState::LoadAssets(){}

void EndState::Start() {
}

void EndState::Pause() {
	backgroundMusic.Stop(0);
}

void EndState::Resume() {}