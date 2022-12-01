#include "State.h"

State::State(){
    quitRequested = false;
    popRequested = false;
    started = false;
}
State::~State(){
    objectArray.clear();
}
void State::Start() {
	LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}
weak_ptr<GameObject> State::AddObject(GameObject* object){
	shared_ptr<GameObject> sptr(object);
	objectArray.push_back(sptr);
	if(started == true){
		sptr->Start();
	}

	return weak_ptr<GameObject>(sptr);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* object){
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object)
			return weak_ptr<GameObject>(objectArray[i]);
	}
	return weak_ptr<GameObject>();

}

bool State::PopRequested(){
    return popRequested;
}
bool State::QuitRequested(){
    return quitRequested;
}
 void State::StartArray(){
    for(unsigned int i= 0; i < objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started =true;
}
 void State::UpdateArray(float dt){
    for(unsigned int i= 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}
 void State::RenderArray(){
    for(unsigned int i= 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}
