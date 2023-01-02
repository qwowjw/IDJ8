#include "TitleState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState.h"
#include "ChooseState.h"
#include "StageState2.h"
#include "Camera.h"
#include "Game.h"
#include "Text.h"


TitleState::TitleState(){
	quitRequested = false;
    GameObject* gobgsprite = new GameObject();
    Sprite* sprite = new Sprite(*gobgsprite, "assets/img/tema.png");
	gobgsprite->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
	gobgsprite->AddComponent(sprite);
	objectArray.emplace_back(gobgsprite);

	GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/CALDERIOUS.ttf", 60, Text::TextStyle::BLENDED, "JOGAR", SDL_Color{ 255,165,0 });
	gofont->AddComponent(text);
	gofont->box.SetCentro(280 / 2, 160);
	objectArray.emplace_back(gofont);

	GameObject* gofont2 = new GameObject();
	gofont2->box = Rect(0, 0, 0, 0);
	Text* text2 = new Text(*gofont2, "assets/font/CALDERIOUS.ttf", 60, Text::TextStyle::BLENDED, "OPCOES", SDL_Color{ 0,165,0 });
	gofont2->AddComponent(text2);
	gofont2->box.SetCentro(280 / 2, 460);
	objectArray.emplace_back(gofont2);
	
	timer = Timer();
	texten = true;
}
TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(float dt){
    quitRequested = false;
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && ((mouseX >= 18) && (mouseX <= 260) && (mouseY >= 131) && (mouseY <= 177))){
		//cout << mouseX << endl;
		//cout << mouseY << endl; 
		Game::GetInstance().Push(new StageState());
	}
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&((mouseX <= 280) && (mouseY >= 432) && (mouseY <= 472))){
		//ChooseState* chooseState = new ChooseState();
		Game::GetInstance().Push(new ChooseState());
	}
	/*
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested() == true) {
		quitRequested = true;
	}
    else if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		Game::GetInstance().Push(new StageState());
	}
	*/
	if (texten && timer.Get() > 1) {
		Text* text = (Text*)objectArray[1]->GetComponent("Text");
		if (text != nullptr) {
			text->SetColor(SDL_Color{ 0xFF,0xFF,0xFF});
			texten = false;
			timer.Restart();
		}
	}
	else if (!texten && timer.Get() > 1) {
		Text* text = (Text*)objectArray[1]->GetComponent("Text");
		if (text != nullptr) {
			text->SetColor(SDL_Color{ 255,165,0});
			texten = true;
			timer.Restart();
		}
	}
	timer.Update(dt);
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Start() {
	StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {}