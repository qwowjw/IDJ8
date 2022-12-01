#include "State.h"
#include "Alien.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Collision.h"
#include "StageState2.h"
#include "EndState.h"
#include "GameData.h"
#include "Text.h"

StageState2::StageState2() : State() {
    quitRequested = false;
	started = false;
	backgroundMusic = nullptr;
	tileSet = nullptr;
}
StageState2::~StageState2() {
    objectArray.clear();
}

void StageState2::LoadAssets(){
	GameObject* bg1 = new GameObject;
	
	Sprite* sprite = new Sprite(*bg1, "assets/img/ocean.jpg");
	bg1->box.x = 0;
	bg1->box.y = 0;
	bg1->box.w = sprite->GetWidth();
	bg1->box.h = sprite->GetHeight();
	bg1->AddComponent(sprite);
	CameraFollower* update = new CameraFollower(*bg1);
	bg1->AddComponent(update);
	objectArray.emplace_back(bg1);

	
    backgroundMusic = new Music("assets/audio/stageState.ogg");
	backgroundMusic->Play();

	GameObject* gt = new GameObject;
	TileSet* ts = new TileSet(*gt, 64, 64, "assets/img/tileset.png");
	TileMap* tm = new TileMap(*gt, "assets/map/tileMap.txt", ts);
	gt->AddComponent(tm);
	objectArray.emplace_back(gt);

	GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/Call me maybe.ttf", 60, Text::TextStyle::BLENDED, "Fase 2", SDL_Color{ 255,0,0, 255 });
	gofont->AddComponent(text);
	gofont->box.SetCentro(1024 / 2, 560);
	objectArray.emplace_back(gofont);

	for (unsigned int i = 0; i < 6; i++) {
		GameObject* alien = new GameObject();
		alien->AddComponent(new Alien(*alien, 5));
		alien->box.x = (rand() % 1408) - (alien->box.w/2);
		alien->box.y = (rand() % 1280) - (alien->box.h/2);
		objectArray.emplace_back(alien);
	}

	GameObject* penguin = new GameObject();
		Sprite* penguinsprite = new Sprite(*penguin, "assets/img/ferrarisemfogo.png");
	penguin->box.SetCentro(704, 640);
	penguin->box.h = penguinsprite->GetHeight();
	penguin->box.w = penguinsprite->GetWidth();
	penguin->AddComponent(penguinsprite);
	penguin->AddComponent(new PenguinBody(*penguin));
	objectArray.emplace_back(penguin);


}

void StageState2::Update(float dt) {
	Camera::Update(dt);
	quitRequested = false;
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested() == true) {
		quitRequested = true;
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider* a = (Collider*)objectArray[i]->GetComponent("Collider");
		if (a != nullptr) {
			for (unsigned int j = i + 1; j < objectArray.size(); j++) {
				Collider* b = (Collider*)objectArray[j]->GetComponent("Collider");
				if (b != nullptr) {
					if (Collision::IsColliding(a->GetHitbox(), b->GetHitbox(), a->associated.angleDeg, b->associated.angleDeg)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
 		}
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;
		}
	}
	bool achou = false;
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		PenguinBody* pb = (PenguinBody*)objectArray[i]->GetComponent("PenguinBody");
		if (pb != nullptr) {
			achou = true;
		}
	}
	if (!achou) {
		Camera::Unfollow();
		Camera::pos = Vec2(0, 0);
		popRequested = true;
		GameData::playerVictory = false;
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}
	if (!Alien::alienCount) {
		Camera::Unfollow();
		Camera::pos = Vec2(0, 0);
		popRequested = true;
		GameData::playerVictory = true;
		GameData::fase2 = true;
		
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}

}
void StageState2::Render() {
	TileMap* tm1 = nullptr;
	TileMap* tm = nullptr;
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		tm1 = (TileMap*)objectArray[i]->GetComponent("TileMap");
		if (tm1 != nullptr) {
			tm = tm1;
			tm->RenderLayer(0, Camera::pos.x, Camera::pos.y);
		}
		else
			objectArray[i]->Render();
	}
	if (tm != nullptr) {
		tm->RenderLayer(1, Camera::pos.x, Camera::pos.y);
	}
}
void StageState2::Start(){
    LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void StageState2::Pause() {

}
void StageState2::Resume(){

}