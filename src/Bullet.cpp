#include "Bullet.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated) {
    Vec2 speedtmp = Vec2(speed,0);
    associated.angleDeg = angle * 180 / PI;
	this->speed = speedtmp.Rotate(angle);
	this->targetsPlayer = targetsPlayer;
	distanceLeft = maxDistance;
	this->damage = damage;
	Sprite * spritetmp = new Sprite(associated, sprite, frameCount, 0.1);
	associated.box.w = spritetmp->GetWidth();
	associated.box.h = spritetmp->GetHeight();
	associated.AddComponent(spritetmp);
    associated.AddComponent(new Collider(associated));

}

void Bullet::Update(float dt) {
    Vec2 distpercorrida;
	associated.box.SetCentro(associated.box.GetVecCentralizado() + speed * dt);
    //associated.box.SetCentro(associated.box.GetVecCentralizado().x + speed.x * dt, associated.box.GetVecCentralizado().y + speed.y * dt);
	distpercorrida = Vec2(speed * dt);
	distanceLeft -= distpercorrida.Magnitude();
	if (distanceLeft <= 0) {

		associated.RequestDelete();
	}

}

void Bullet::Render(){

}

bool Bullet::Is(string type){
    return type == "Bullet";

}
int Bullet::GetDamage(){
	associated.RequestDelete();
    return damage;

}
void Bullet::NotifyCollision(GameObject& other) {
	/*Bullet* pb = (Bullet*)other.GetComponent("Bullet");
	if (pb == nullptr) {
		associated.RequestDelete();
	}*/
}