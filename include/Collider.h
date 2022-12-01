#ifndef COLLIDER_H
#define COLLIDER_H
#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"
#include "PenguinBody.h"
#include "Collider.h"


using namespace std;

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1,0.5}, Vec2 offset ={0,0.5});
    void Update(float dt);
    void Render();
    Rect GetHitbox();
    bool Is (string type);
    void SetScale (Vec2 scale);
    void  SetOffset (Vec2 offset);
private:
    Vec2 scale;
    Vec2 offset;

};

#endif