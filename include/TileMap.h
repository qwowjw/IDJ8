#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include "Component.h"
#include "TileSet.h"
#include <fstream>
#include <Camera.h>

using namespace std;
class TileMap : public Component{
public:
	TileMap(GameObject& associated, string file, TileSet* tileSet);
	~TileMap();
	void Load(string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z);
	void Render();
	virtual void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	bool Is(string type);
	void Update(float dt);
private:
	vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};
#endif