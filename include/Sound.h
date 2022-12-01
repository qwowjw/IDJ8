#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <string>
#include "Component.h"
#include "GameObject.h"
#if defined (_WIN64) || defined (_WIN32)
#include <SDL2/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif
using namespace std;

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();
    void Update(float dt);
    void Render();
    bool Is(string type);
private:
    Mix_Chunk* chunk;
    int channel;
};
#endif