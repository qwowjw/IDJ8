#ifndef TILESET_H
#define TILESET_H
#include "GameObject.h"
#include <string>
#include "Rect.h"
#include "Sprite.h"
using namespace std; 
class TileSet{
public:
	TileSet(GameObject& associated, float tileWidth, float tileHeight, string file);
	void RenderTile(int index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();
private:
	Sprite* tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};
#endif

