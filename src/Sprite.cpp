#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	scale = Vec2(1,1);
    frameCount = 1;
    currentFrame = 0;
    timeElapsed = 0;
    frameTime = 1;
}

Sprite::~Sprite() {
	/*if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}*/
}
void Sprite::Open(string file) {
	/*texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (texture == nullptr) {
		SDL_Log("Unable to load Texture: %s", SDL_GetError());
		exit(-1);
	}*/
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	this->file = file;
}
void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	SDL_Rect dstRect;
	dstRect.x = associated.box.x - Camera::pos.x;
	dstRect.y = associated.box.y - Camera::pos.y;
	dstRect.h = height * scale.y;
	dstRect.w = width * scale.x / frameCount;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);

	
}
void Sprite::Render(float x, float y, float w, float h){
	SDL_Rect dstRect;
	dstRect.x = nearbyint(x);
	dstRect.y = nearbyint(y);
	dstRect.h = nearbyint(h);
	dstRect.w = nearbyint(w);
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() {
	return width / frameCount * scale.x;
}
int Sprite::GetHeight() {
	return height * scale.y;
}
bool Sprite::IsOpen() {
	return texture != nullptr;
}
void Sprite::Update(float dt){
	timeElapsed += dt;
	selfDestructCount.Update(dt);
	if (timeElapsed > frameTime) {
		timeElapsed = 0;
		currentFrame++;
		if (currentFrame > frameCount - 1) {
			currentFrame = 0;
		}
		SetFrame(currentFrame);
	}
	if (secondsToSelfDestruct && (secondsToSelfDestruct < selfDestructCount.Get())){
		associated.RequestDelete();
	}
}
Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct ) : Sprite(associated){
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	selfDestructCount = Timer();
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->currentFrame = 0;
	this->timeElapsed = 0;
	texture = nullptr;
	Open(file);
	SetClip(0, 0, width, height);
	scale = Vec2(1,1);
	SetFrame(0);
}
bool Sprite::Is(string type){
	
	return type == "Sprite" ? true : false;
}
void Sprite::SetScaleX(float scaleX, float scaleY) {
	scale = Vec2(scaleX, scaleY);
	Vec2 Centro = associated.box.GetVecCentralizado();
	associated.box.x *= scale.x;
	associated.box.y *= scale.y;
	associated.box.SetCentro(Centro);
	associated.angleDeg = 180 * 180 / PI - 90;
}
Vec2 Sprite::GetScale(){
	return scale;
}

void Sprite::SetFrame(int frame){
	int x = frame * width/frameCount;
	int y = 0;
	int w = width/frameCount;
	int h = height;
	SetClip(x, y, w, h);

}
void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}
void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;
}