#include "Rect.h"
Rect::Rect(){
	x=y=w=h=0;
}

Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

}

Rect::~Rect(){
}

bool Rect::Contains(float x, float y){
	return x >= this->x && x <= this->x + w && y >= this->y && y <= this->y + h;
}

bool Rect::Contains(Vec2 b){
	return b.x >= this->x && b.x <= this->x + w && b.y >= this->y && b.y <= this->y + h;
}

void Rect::SetCentro(float x, float y) {
	this->x = x - w / 2;
	this->y = y - h / 2;
}

void Rect::SetCentro(Vec2 v) {
	this->x = v.x - w / 2;
	this->y = v.y - h / 2;
}
Vec2 Rect::GetVecCentralizado() {
	return Vec2(x + w / 2, y + h / 2);
}