#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "Resources.h"
#include "Component.h"
#include "Timer.h"
#include "GameObject.h"
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#endif
using namespace std;
class Sprite : public Component {
public:
    Sprite(GameObject& associated);

    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
	void Render(float x, float y, float w, float h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Update(float dt);
    bool Is(string type);
    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();
    Sprite(GameObject& associated, string file, int frameCount=1, float frameTime =1, float secondsToSelfDestruct=0);
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
private:
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    float secondsToSelfDestruct;
    Timer selfDestructCount;
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    string file;
    Vec2 scale;
};
#endif