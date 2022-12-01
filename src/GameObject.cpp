#include "GameObject.h"
GameObject::GameObject() {
	isDead=false;
	started = false;
	angleDeg = 0;
}
GameObject::~GameObject() {
	for (int i = components.size() - 1; i >= 0; i--) {
		components.erase(components.begin()+i);
	}
	components.clear();
}
void GameObject::Update(float dt) {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Update(dt);
	}
}
void GameObject::Render() {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Render();
	}
}
void GameObject::Start(){
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Start();
	}

}
bool GameObject::IsDead() {
	return isDead;
}
void GameObject::RequestDelete() {
	isDead = true;
}
void GameObject::AddComponent(Component* cpt) {
	components.emplace_back(cpt);
}
void GameObject::RemoveComponent(Component* cpt) {
	bool found = false;
	for (unsigned int i = 0; i < components.size() && !found; i++) {
		if (components[i].get() == cpt) {
			components.erase(components.begin() + i);
			found = true;
		}
	}
}
void GameObject::RemoveComponent(string type) {
	bool found = false;
	for (unsigned int i = 0; i < components.size() && !found; i++) {
		if (components[i]->Is(type)) {
			components.erase(components.begin() + i);
			found = true;
		}
	}
}

Component* GameObject::GetComponent(string type) {
	for (unsigned int i = 0; i < components.size(); i++) {
		if (components[i]->Is(type)) {
			return components[i].get();
		}
	}
	return nullptr;
}
void GameObject::NotifyCollision(GameObject& other) {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->NotifyCollision(other);
	}
}