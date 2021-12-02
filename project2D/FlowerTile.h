#pragma once
#include "Tile.h"

class FlowerTile : public Tile
{
public:
	FlowerTile();
	FlowerTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~FlowerTile();
};
