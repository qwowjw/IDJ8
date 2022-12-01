#ifndef RECT_H
#define RECT_H
#include "Vec2.h"
using namespace std;
class Rect {
public:
    Rect();
    Rect(float x, float y, float w, float h);
    ~Rect();
    float x, y, h, w;
    bool Contains(float x, float y);
    bool Contains(Vec2 b);
    void SetCentro(float x,float y);
	void SetCentro(Vec2 vect);
    Vec2 GetVecCentralizado();

};

#endif
