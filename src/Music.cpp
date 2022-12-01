#include "Music.h"
#include "Resources.h"

Music::Music() {
    music = nullptr;
}
Music::Music(string file) {
    Open(file);
}
void Music::Play(int times) {
    if (music == nullptr) {
        SDL_Log("Unable to initialize Music Play: %s", SDL_GetError());
        exit(-1);
    }
    Mix_PlayMusic(music, times);
}
void Music::Stop(int msToStop) {
    int Mix_FadeOutMusic(int msToStop);
}
void Music::Open(string file) {
    music = Resources::GetMusic(file);
    //-music = Mix_LoadMUS(file.c_str());
    //if (music == nullptr) {
        //SDL_Log("Unable to initialize Music Open: %s", SDL_GetError());
       // exit(-1);
    //};
}
bool Music::IsOpen() {
    return music != nullptr;
}
Music::~Music() {
    //Stop();
    //Mix_FreeMusic(music);
}
