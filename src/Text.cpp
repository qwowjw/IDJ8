#include "Text.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated) {
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	texture = nullptr;
	font = Resources::GetFont(fontFile, fontSize);
	RemakeTexture();
}

Text::~Text() {
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Text::Update(float dt) {

}


void Text::Render() {
	SDL_Rect dstRect, clipRect;
	dstRect.x = associated.box.x - Camera::pos.x;
	dstRect.y = associated.box.y - Camera::pos.y;
	dstRect.h = associated.box.h;
	dstRect.w = associated.box.w;
	clipRect = dstRect;
	clipRect.x = clipRect.y = 0;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
	//cout << "renderizando fonte" << endl;
}

void Text::SetText(string text) {
	this->text = text;
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
}

void Text::RemakeTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surfacetmp = nullptr;
	switch (style) {
	case SOLID:
		surfacetmp = TTF_RenderText_Solid(font, text.c_str(), color);
		break;
	case SHADED:
		surfacetmp = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color{ 0,0,0});
		break;
	case BLENDED:
		surfacetmp = TTF_RenderText_Blended(font, text.c_str(), color);
		break;
	default:
		surfacetmp = TTF_RenderText_Solid(font, text.c_str(), color);
		break;
	}
	if (surfacetmp == nullptr) {
		cout << "Deu ruim" << endl;
		exit(-1);
	}
	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surfacetmp);
	if (texture == nullptr) {
		cout << "Deu ruim" << endl;
		exit(-1);
	}
	SDL_FreeSurface(surfacetmp);
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	associated.box.w = w;
	associated.box.h = h;
}

bool Text::Is(string type) {
	return type == "Text";
}