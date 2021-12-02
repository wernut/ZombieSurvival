#pragma once
#include "Tile.h"
class WoodPlankTile : public Tile
{
public:
	WoodPlankTile();
	WoodPlankTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~WoodPlankTile();
};
