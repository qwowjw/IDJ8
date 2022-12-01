#ifndef ALIEN_H
#define ALIEN_H
#include <string>
#include "ALien.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Minion.h"
#include "Timer.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sound.h"
#include <float.h>
#include <queue>

using namespace std;

class Alien : public Component{
public:
    Alien(GameObject& associated,int nMinionsfloat,  float secondsCD = 5);
    ~Alien();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    Vec2 dist;
    void NotifyCollision(GameObject& other);
    float arc1;
    static int alienCount;
private:

    public:
	enum AlienState { MOVING, RESTING };
	AlienState state;
	Timer restTimer;
	Vec2 destination;
	Vec2 speed;
    float secondsCD;
	float hp;
	bool dead;
	int nMinions;
	vector<weak_ptr<GameObject>> minionArray;
};

#endif
