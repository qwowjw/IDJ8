#include "Vec2.h"
float Vec2::Magnitude() {
	return sqrt(x * x + y * y);
}
Vec2 Vec2::operator+(Vec2 const& vect) {
	return Vec2(x + vect.x, y+ vect.y);
}
Vec2 Vec2::operator-(Vec2 const& vect) {
	return Vec2(x - vect.x, y - vect.y);
}
Vec2 Vec2::operator*(Vec2 const& vect) {
	return Vec2(x * vect.x, y * vect.y);
}
Vec2 Vec2::operator*(float const& esc) {
	return Vec2(x * esc, y * esc);
}

Vec2::Vec2(float x, float y){
	this->x = x;
	this->y = y;
}
Vec2 Vec2::Normalizado(){
	return Vec2(x / Magnitude(), y / Magnitude());
}
Vec2::Vec2(){
	x = 0;
	y = 0;
}
Vec2 Vec2::Rotate(float angulo) {
	return Vec2(x * cos(angulo) - y * sin(angulo), y * cos(angulo) + x * sin(angulo));
}

float Vec2::Inclinacao() {
	return atan2(y, x);
}

void Vec2::operator+=(Vec2 b) {
	x += b.x;
	y += b.y;
}

Vec2 Vec2::operator/(float d) const{
	return Vec2(x/d, y/d);
}