#include "Resources.h"
#include "Game.h"
unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;
unordered_map<string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(string file) {
    unordered_map<string, SDL_Texture*>::const_iterator achou = imageTable.find(file);
    if (achou == imageTable.end()) {
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr) {
            SDL_Log("Unable to load Texture in Resources: %s", SDL_GetError());
            exit(-1);
        }
        imageTable.emplace(file, texture);
        return texture;
    }
    return achou->second;
}

void Resources::ClearImages() {
    for (auto& a : imageTable) {
        SDL_DestroyTexture(a.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file) {
    unordered_map<string, Mix_Music*>::const_iterator achou = musicTable.find(file);
    if (achou == musicTable.end()) {
        Mix_Music* music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            cerr << Mix_GetError();
            exit(-1);
        }
        musicTable.emplace(file, music);
        return music;
    }
    return achou->second;
}

void Resources::ClearMusics() {
    for (auto& a : musicTable) {
        Mix_FreeMusic(a.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file) {
    unordered_map<string, Mix_Chunk*>::const_iterator achou = soundTable.find(file);
    if (achou == soundTable.end()) {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr) {
            cerr << Mix_GetError();
            exit(-1);
        }
        soundTable.emplace(file, chunk);
        return chunk;
    }
    return achou->second;
}

void Resources::ClearSounds() {
    for (auto& a : soundTable) {
        Mix_FreeChunk(a.second);
    }
    soundTable.clear();
}
TTF_Font* Resources::GetFont(string file, int fontSize) {
	string key = file + to_string(fontSize);
	unordered_map<string, TTF_Font*>::const_iterator achou = fontTable.find(key);
	if (achou == fontTable.end()) {
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if (font == nullptr) {
			cerr << TTF_GetError();
			exit(-1);
		}
		fontTable.emplace(key, font);
		return font;
	}
	return achou->second;
}

void Resources::ClearFonts() {
	for (auto& a : fontTable) {
		TTF_CloseFont(a.second);
	}
	fontTable.clear();
}