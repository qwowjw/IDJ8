#include "Camera.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = {0,0};
Vec2 Camera::speed;

void Camera::Update(float dt){
	const float speed_mag = 100; 

	speed = Vec2();
	if (focus != nullptr) {
		pos.x = focus->box.x - SCREEN_WIDTH/2.0 + focus->box.w/2.0;
		pos.y = focus->box.y - SCREEN_HEIGHT/2.0 + focus->box.h/2.0;

	}
	else {
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
			speed.y +=  -speed_mag;
		}
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
			speed.y +=  +speed_mag;
		}
		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			speed.x += -speed_mag;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
			speed.x += +speed_mag;
		}

		pos.x = pos.x + speed.x*dt;
		pos.y = pos.y + speed.y*dt;

	}

}
void Camera::Unfollow() {
	focus = nullptr;
}
void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}
