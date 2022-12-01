#include "Minion.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

Minion::Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter){
	arc = arcOffsetDeg;
    associated.AddComponent(new Collider(associated));
}
void Minion::Update(float dt){
    Vec2 pos = Vec2(170,0);
    float f = 150;
    pos = pos.Rotate(arc);
    pos += alienCenter.box.GetVecCentralizado();
    associated.box.SetCentro(pos);
    associated.angleDeg = arc * 180 / PI - 90;
	arc += 2 * PI * f * dt/1000;
	if (arc > 2 * PI){
        arc -= 2 * PI;
    }
		
}
void Minion::Render(){

}

bool Minion::Is(string type){
    return type == "Minion";
}

void Minion::Shoot(Vec2 target){
    Vec2 direcao = target - associated.box.GetVecCentralizado();
    GameObject* tmp = new GameObject();
    tmp->box.x = associated.box.GetVecCentralizado().x;
    tmp->box.y = associated.box.GetVecCentralizado().y;
    Bullet* bullet = new Bullet(*tmp, direcao.Inclinacao(), 150, 10, 1000,  "assets/img/minionbullet2.png", true, 3);
	tmp->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(tmp);
}
