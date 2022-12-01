#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "Component.h"
#include "Rect.h"
#include <memory>
#include <vector>
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif
using namespace std;

class Component;
class GameObject{
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	void Start();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	void RemoveComponent(string type);
	Component* GetComponent(string type);
    void NotifyCollision(GameObject& other);

	Rect box;
	bool started;
	double angleDeg;
private:
	vector<shared_ptr<Component>> components;
	bool isDead;
};
#endif

