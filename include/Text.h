#ifndef TEXT_H
#define TEXT_H
#include "Component.h"
#if defined (_WIN64) || defined (_WIN32)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stack>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

class Text : public Component {
public:
	enum TextStyle {SOLID, SHADED, BLENDED};
	Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
	~Text();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void SetText(string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(string fontFile);
	void SetFontSize(int fontSize);
private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	string text;
	TextStyle style;
	string fontFile;
	int fontSize;
	SDL_Color color;
};

#endif