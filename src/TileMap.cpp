#include "../include/TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) :  Component (associated){
	Load(file);
	this->tileSet = tileSet;
    //associated.box = Rect(0, 0, tileSet->GetColumns() * tileSet->GetTileWidth(), tileSet->GetRows() * tileSet->GetTileHeight());
    //cout << associated.box << endl;
}

TileMap::~TileMap(){}

void TileMap::Load(string file){
    ifstream fin;
    int tmp;
    char discard;
    fin.open(file);
    fin >> mapWidth >> discard >> mapHeight >> discard >> mapDepth;
    for (int i = 0; i < mapDepth; i++) {
        fin >> discard;
        for (int j = 0; j < mapHeight; j++) {
            for (int k = 0; k < mapWidth; k++) {
                fin >> tmp >> discard;
                tmp--;
                tileMatrix.push_back(tmp);
            }
        }
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int tmp;
    tmp = z * mapWidth * mapHeight + y * mapWidth + x;
    return tileMatrix[tmp];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            tileSet->RenderTile(At(j, i, layer), ( j  *tileSet->GetTileWidth())- Camera::pos.x * 2 * (layer+0.5), ( i * tileSet->GetTileHeight()) - Camera::pos.y * 2 * (layer+0.5));
        }
    }

}

void TileMap::Render() {
    for (int i = 0; i < mapDepth; i++) {
        RenderLayer(i);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}
int TileMap::GetHeight() {
    return mapHeight;
}
int TileMap::GetDepth() {
    return mapDepth;
}

bool TileMap::Is(string type) {
    return type == "TileMap";
}

void TileMap::Update(float dt){}
