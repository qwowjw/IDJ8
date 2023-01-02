#include "ChooseState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState2.h"
#include "Text.h"
#include "Camera.h"
#include "StageState.h"
#include "TitleState.h"

ChooseState::~ChooseState() {
    objectArray.clear();
}
ChooseState::ChooseState() {
	quitRequested = false;

    GameObject* gobgsprite = new GameObject();
    Sprite* sprite = new Sprite(*gobgsprite, "assets/img/heimdall.jpg");
	gobgsprite->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
	gobgsprite->AddComponent(sprite);
	objectArray.emplace_back(gobgsprite);
	
    
    GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/Nadine.ttf", 60, Text::TextStyle::BLENDED, "Fase 1", SDL_Color{ 255,165,0 });
	gofont->AddComponent(text);
	gofont->box.SetCentro(280 / 2, 160);
	objectArray.emplace_back(gofont);

	GameObject* gofont2 = new GameObject();
	gofont2->box = Rect(0, 0, 0, 0);
	Text* text2 = new Text(*gofont2, "assets/font/Nadine.ttf", 60, Text::TextStyle::BLENDED, "Fase 2", SDL_Color{ 0,165,0 });
	gofont2->AddComponent(text2);
	gofont2->box.SetCentro(280 / 2, 460);
	objectArray.emplace_back(gofont2);
    
	/*else if ((GameData::playerVictory == true)&& (GameData::fase2 == false)) {
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
	}*/
}

void ChooseState::Update(float dt) {
    quitRequested = false;
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
	/* (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
		cout << mouseX << endl;
		cout << mouseY << endl;
	}*/
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && ((mouseX >= 75) && (mouseX <= 203) && (mouseY >= 134) && (mouseY <= 172))){ 
		Game::GetInstance().Push(new StageState());
	}
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&((mouseX >= 70) && (mouseX <= 207) && (mouseY >= 436) && (mouseY <= 473))){
		StageState2* stageState2 = new StageState2();
		Game::GetInstance().Push(new StageState2());
    }

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		popRequested = true;
	}
}

void ChooseState::Render() {
	RenderArray();
}

void ChooseState::LoadAssets(){}

void ChooseState::Start() {
}

void ChooseState::Pause() {
	backgroundMusic.Stop(0);
}

void ChooseState::Resume() {}