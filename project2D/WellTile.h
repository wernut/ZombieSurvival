#pragma once
#include "Tile.h"
class WellTile : public Tile
{
public:
	WellTile();
	WellTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~WellTile();

	bool IsSolid();
};

