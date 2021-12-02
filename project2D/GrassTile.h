#pragma once
#include "Tile.h"

class GrassTile : public Tile
{
public:
	GrassTile();
	GrassTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~GrassTile();
};
