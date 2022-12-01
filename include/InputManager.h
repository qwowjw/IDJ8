#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <SDL2/SDL.h>
#include "SDL_include.h"
#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define W_KEY SDLK_w
#define E_KEY SDLK_e
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d
#define SPACE_KEY	SDLK_SPACE
using namespace std;

class InputManager{
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	~InputManager();
	static InputManager& GetInstance();
private:
	InputManager();
	bool mouseState[6];
	int mouseUpdate[6];
	unordered_map<int, bool> keyState;
	unordered_map<int, int> keyUpdate;
	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;
};
#endif

