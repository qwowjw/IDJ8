#ifndef RESOURCES_H
#define RESOURCES_H
#include <unordered_map> 
#include <string>
#include "GameObject.h"
#include "Game.h"
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_ttf.h>
#endif
using namespace std;
class Resources {
public:
	static SDL_Texture* GetImage(string file);
	static void ClearImages();
	static Mix_Music* GetMusic(string file);
	static void ClearMusics();
	static Mix_Chunk* GetSound(string file);
	static void ClearSounds();
	static TTF_Font* GetFont(string file, int fontSize);
	static void ClearFonts();
	
private:
	static unordered_map<string, SDL_Texture*> imageTable;
	static unordered_map<string, Mix_Music*> musicTable;
	static unordered_map<string, Mix_Chunk*> soundTable;
	static unordered_map<string, TTF_Font*> fontTable;

};
#endif