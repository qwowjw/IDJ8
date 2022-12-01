#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "Camera.h"
#include <string>
#include "GameObject.h"
#include "InputManager.h"

using namespace std;

class CameraFollower: public Component{
public:
    CameraFollower(GameObject& go);
    void Update(float dt);
    void Render();
    bool Is(string type);
};
#endif
