#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H
#include <string>
#include "GameObject.h"
using namespace std; 
#include "Timer.h"

class PenguinCannon : public Component {
public:
    PenguinCannon (weak_ptr<GameObject> penguinBody, GameObject& associated);
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);
    void Shoot();

private:
    weak_ptr<GameObject> pbody;
    float angle;
    Timer timer;

};
#endif