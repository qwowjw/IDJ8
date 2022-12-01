#include "PenguinCannon.h"
#include "Bullet.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinBody.h"
#include "Collider.h"


PenguinCannon::PenguinCannon(weak_ptr<GameObject> penguinBody, GameObject& associated) : Component (associated) {
	pbody = penguinBody;
	associated.AddComponent(new Collider(associated));
	timer = Timer(5);

}
void PenguinCannon::Update(float dt) {
	if (pbody.lock() == nullptr) {
		associated.RequestDelete();
	}
	else {
		
		if(!pbody.expired()) {
			auto& p = *pbody.lock();
			associated.box.SetCentro(p.box.GetVecCentralizado());
		}
		
		Vec2 mousePos(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
		angle = (mousePos + Camera::pos - associated.box.GetVecCentralizado()).Inclinacao();
		associated.angleDeg = angle * 180 / PI;
		timer.Update(dt);

		if (timer.Get() >0.5){
			if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
					Shoot();
					timer.Restart();
			}
		}
	}
}

void PenguinCannon::Shoot() {
	GameObject* tmp = new GameObject();
	Vec2 offset = Vec2(70,0).Rotate(angle);
	Bullet* bullet = new Bullet(*tmp, angle, 500, 10, 1000, "assets/img/penguinbullet.png", false, 4);
	tmp->box.SetCentro(associated.box.GetVecCentralizado() + offset);
	tmp->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(tmp);
}
void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type) {
	return type == "PenguinCannon";
}

void PenguinCannon::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet) {
		PenguinBody::player->NotifyCollision(other);
	}
}