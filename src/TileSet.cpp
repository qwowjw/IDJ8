#include "TileSet.h"
TileSet::TileSet(GameObject& associated, float tileWidth, float tileHeight, string file) {
	this->tileHeight = (int)tileHeight;
	this->tileWidth = (int)tileWidth;
	tileSet = new Sprite(associated, file);
    rows = tileSet->GetHeight() / tileHeight;
    columns = tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(int index, float x, float y) {
    if (index >= 0 && index < rows * columns) {
        int i, j;
        float a, b, w, h;
        Rect dstRect(x, y, tileWidth, tileHeight);
        i = index % columns;
        j = index / columns;
        a = i * tileWidth;
        b = j * tileHeight;
        w = tileWidth;
        h = tileHeight;
        tileSet->SetClip(a, b, w, h);
        tileSet->Render(x,y,w,h);
    }
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}
