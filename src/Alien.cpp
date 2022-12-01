#include "Alien.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
int Alien::alienCount = 0;
Alien::Alien(GameObject& associated,int nMinions, float secondsCD) : Component(associated){
    hp = 30;
    speed = {0,0};
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
	//associated.box.x = 512;
	//associated.box.y = 300;
	associated.box.w = sprite->GetWidth();
	associated.box.h = sprite->GetHeight();
	this->nMinions = nMinions;
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	alienCount++;
	state = RESTING;
	dead = false;
	this->secondsCD = secondsCD;
}
void Alien::Start(){
	auto alienPass = Game::GetInstance().GetState().GetObjectPtr(&associated);
	for (int i = 0; i < nMinions; i++) {
		GameObject* tmp = new GameObject();
		Sprite* sprite = new Sprite(*tmp, "assets/img/minion.png");
		float scale = (rand() % 6 + 10) / 10.0;
		sprite->SetScaleX(scale, scale);
		tmp->box.w = sprite->GetWidth();
		tmp->box.h = sprite->GetHeight();
		tmp->box.x = associated.box.x;
		tmp->box.y = associated.box.y;
		tmp->AddComponent(sprite);
		tmp->AddComponent(new Minion(*tmp, associated, i * 2 * PI / nMinions));
		minionArray.push_back(Game::GetInstance().GetState().AddObject(tmp));
	}
}
Alien::~Alien(){
	minionArray.clear();
	alienCount--;
}
void Alien::Update(float dt){
    /*associated.angleDeg =  arc1 * 1080 / PI - 90;
	arc1 -= 2 * PI * 15 * dt/750;
	if (arc1 > 2 * PI){
        arc1 -= 2 * PI;
	}*/
	/*int spd = 256;

    
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Alien::Action::ActionType::SHOOT, mouseX, mouseY));
	}
	else if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Alien::Action::ActionType::MOVE, mouseX, mouseY));
	}
	speed = {0,0};
	Vec2 alien_pos = {associated.box.x,associated.box.y};

	if (!taskQueue.empty()) {
		float min = FLT_MAX;
		Action sptr = taskQueue.front();
		if (sptr.type == Action::ActionType::MOVE){
            Vec2 destiny_center;
            destiny_center.x = sptr.pos.x - associated.box.w/2;
            destiny_center.y = sptr.pos.y - associated.box.h/2;
			
            speed += (destiny_center - alien_pos).Normalizado();
            associated.box.x += speed.x*dt*200;
            associated.box.y += speed.y*dt*200;

			Vec2 dist = destiny_center;

            if(abs((destiny_center - alien_pos).Magnitude()) <= 5){
				associated.box.x = destiny_center.x;
				associated.box.y = destiny_center.y;
                taskQueue.pop();
            }
        }
		else if (sptr.type == Action::ActionType::SHOOT) {
			Vec2 destiny_center;
			Minion* selected = nullptr;
			for (int i = 0; i < minionArray.size(); i++) {
				shared_ptr<GameObject> go= minionArray[i].lock();
				Minion* m = (Minion*)go->GetComponent("Minion");
				float dist = abs((m->associated.box.GetVecCentralizado() - sptr.pos).Magnitude());
				if (dist < min) {				
					selected = m;
					min = dist;
				}
			}
			selected -> Shoot(sptr.pos);
			taskQueue.pop();
	}
	if (hp <= 0) {
		associated.RequestDelete();
	}*/
	
	const float linear_speed = 200;

	if (state == RESTING) {
		restTimer.Update(dt);
		if (restTimer.Get() > secondsCD) {
			if (PenguinBody::player != nullptr) {
				destination = PenguinBody::player->associated.box.GetVecCentralizado();
				destination.x += (rand() % 500) - 250;
				destination.y += (rand() % 200) -100;
				speed = (destination - associated.box.GetVecCentralizado()).Normalizado()*linear_speed;
			
				state = MOVING;
			}
		}
	}
	
	if (state == MOVING) {
		Vec2 step = speed * dt;

		if (step.Magnitude() > (associated.box.GetVecCentralizado() - destination).Magnitude()) {
			destination = PenguinBody::player->associated.box.GetVecCentralizado();
			Minion* selected = nullptr;
			float min = FLT_MAX;
			for (unsigned int i = 0; i < minionArray.size(); i++) {
				shared_ptr<GameObject> tmp = minionArray[i].lock();
				float dist = (tmp->box.GetVecCentralizado() - destination).Magnitude();
				if (dist < min) {
					selected = (Minion*)tmp->GetComponent("Minion");
					min = dist;
				}
			}
			selected->Shoot(PenguinBody::player->associated.box.GetVecCentralizado());
			state = RESTING;
			restTimer.Restart();
		} else 
			associated.box.SetCentro(associated.box.GetVecCentralizado() + step);
	}
	if (hp <= 0 && !dead) {
		associated.RemoveComponent("Sprite");
		Sprite* sprite = new Sprite(associated, "assets/img/aliendeath.png", 4, 0.25, 1);
		associated.box.w = sprite->GetWidth();
		associated.box.h = sprite->GetHeight();
		associated.box.SetCentro(associated.box.GetVecCentralizado());
		associated.AddComponent(sprite);
		Sound * boom = new Sound(associated, "assets/audio/boom.wav");
		boom->Play();
		for (unsigned int i = 0; i < minionArray.size(); i++) {
			auto minion = minionArray[i].lock();
			Sprite* minionsprite = new Sprite(*minion, "assets/img/miniondeath.png", 4, 0.25, 1);
			minion->box.w = minionsprite->GetWidth();
			minion->box.h = minionsprite->GetHeight();
			minion->RemoveComponent("Sprite");
			minion->AddComponent(minionsprite);
		}
		associated.AddComponent(boom);
		dead = true;
	}
	associated.angleDeg -= (2 * PI * 0.05 * dt / 1000) * 180 / PI;
	if (associated.angleDeg < 0) {
		associated.angleDeg += 360;
	}
	
}

void Alien::Render() {}

bool Alien::Is(string type) {
	return type == "Alien";
}

void Alien::NotifyCollision(GameObject & other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	int var;
	var = (rand() % 3);
	if (bullet != nullptr && !bullet->targetsPlayer) {
		if (var == 1){
			Sound * bill = new Sound(associated, "assets/audio/bora-bill.mp3");
			bill->Play();
			associated.AddComponent(bill);
		}
		else if (var == 2){
			Sound * bill = new Sound(associated, "assets/audio/bora-filho-do-bill.mp3");
			bill->Play();
			associated.AddComponent(bill);
		}
		else{
			Sound * bill = new Sound(associated, "assets/audio/elegosta.mp3");
			bill->Play();
			associated.AddComponent(bill);
		}
		
		hp -= bullet->GetDamage();
	}
}