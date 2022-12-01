#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"

using namespace std;

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount = 1);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
    bool targetsPlayer;
    void NotifyCollision(GameObject& other);
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};
#endif