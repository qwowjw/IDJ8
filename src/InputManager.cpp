#include "../include/InputManager.h"

void InputManager::Update(){
	SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	quitRequested = false;

	updateCounter = updateCounter + 1;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contr�rio
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para termina��o
		if (event.key.repeat == 1) {
			continue;
		}
		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if (event.type == SDL_KEYDOWN) {
			keyState[event.key.keysym.sym] = true;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}
		if (event.type == SDL_KEYUP) {
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;

		}
		
	}
	
}

bool InputManager::KeyPress(int key){
	if ( (keyUpdate[key] == updateCounter) && keyState[key] == true) {
		return true;
	}
	else {
		return false;
	}

}

bool InputManager::KeyRelease(int key){
	if ((keyUpdate[key] == updateCounter) && keyState[key] == false) {
		return true;
	} else {
		return false;
	}

}

bool InputManager::IsKeyDown(int key){
	if (keyState[key] == true) {
		return true;
	} else {
		return false;
	}

}

bool InputManager::MousePress(int button){
	if ((mouseUpdate[button] == updateCounter) && mouseState[button] == true) {
		return true;
	} else {
		return false;
	}
}

bool InputManager::MouseRelease(int button){

	if ((mouseUpdate[button] == updateCounter) && mouseState[button] == false) {
		return true;
	}
	else {
		return false;
	}
}

bool InputManager::IsMouseDown(int button){
	if (mouseState[button] == true) {
		return true;
	}
	else {
		return false;
	}
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}


InputManager::~InputManager(){

}

InputManager::InputManager() {
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
    updateCounter = 0;
    quitRequested = 0;
    mouseX = 0;
    mouseY = 0;
}
