#include "Game.h"
#include "Resources.h"

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) {
    storedState = nullptr;
    frameStart = SDL_GetTicks();
    dt = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL_Init: %s", SDL_GetError());
        exit(-1);
    };
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        SDL_Log("Unable to initialize IMG_INIT: %s", SDL_GetError());
        exit(-1);
    };
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD) == 0) {
        SDL_Log("Unable to initialize MIX_INIT: %s", SDL_GetError());
        exit(-1);
    };
    if (TTF_Init()) {
        SDL_Log("Unable to initialize TTF_Init: %s", SDL_GetError());;
        exit(-1);
    };
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        SDL_Log("Unable to initialize Mix_OpenAudio: %s", SDL_GetError());
        exit(-1);
    };


    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        SDL_Log("Unable to initialize window: %s", SDL_GetError());
        exit(-1);
    };

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
        exit(-1);
    };
}
Game& Game::GetInstance() {
    if (instance == nullptr) {
        Game::instance = new Game("Renato Pedro da Silva Junior| 202063640 ", SCREEN_WIDTH, SCREEN_HEIGHT);
    };
    return *instance;
}

float Game::GetDeltaTime(){
    return dt;
}

void Game::CalculateDeltaTime(){
    int frameAnterior = frameStart;
    frameStart = SDL_GetTicks();
    dt = (frameStart - static_cast<float>(frameAnterior)) / 1000;
}

Game::~Game(){
    if (storedState != nullptr){
        delete(storedState);
    }
    do{
        stateStack.pop();
    } while (!stateStack.empty());
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    TTF_Quit();
    Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

State& Game::GetState() {
    return *stateStack.top();
}
void Game::Push(State* state){
    storedState = state;
}
SDL_Renderer* Game::GetRenderer() {
    return renderer;
}
void Game::Run() {
    if (storedState != nullptr){
        stateStack.emplace(storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }
    else {
        exit(0);
    }
    while (!stateStack.empty() && !stateStack.top()->QuitRequested()) {
        if (stateStack.top()->PopRequested()) {
			stateStack.top()->Pause();
			stateStack.pop();
			if (stateStack.size())
				stateStack.top()->Resume();
		}
		if (storedState != nullptr) {
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			stateStack.top()->Start();
			storedState = nullptr;
		}
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(GetDeltaTime());

        stateStack.top()->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());

        SDL_Delay(33);
    }
}