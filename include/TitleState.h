#ifndef TITLESTATE_H
#define TITLESTATE_H
#include "State.h"
#include "Timer.h"
#include <memory>
#include <vector>
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif
using namespace std;

class TitleState : public State{
public:
    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    private:
	Timer timer;
	bool texten;
};
#endif