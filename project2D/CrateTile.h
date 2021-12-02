#pragma once
#include "Tile.h"


class CrateTile : public Tile
{
public:
	CrateTile();
	CrateTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~CrateTile();
};

