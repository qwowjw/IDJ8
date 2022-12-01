#ifndef MINION_H
#define MINION_H
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Game.h"
#include "Bullet.h"
using namespace std;

class Minion : public Component{
public:
    Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg = 0);
    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot (Vec2 target);
private:
    GameObject& alienCenter;
    float arc;
};
#endif