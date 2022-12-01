#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H
#include <string>
#include "GameObject.h"
#include <list>
using namespace std; 

class PenguinBody : public Component {
public:
    PenguinBody(GameObject& associated);
    ~PenguinBody();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);
    static PenguinBody* player;
    bool dead;
private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
    bool dominicTorettoModeOn;
};
#endif