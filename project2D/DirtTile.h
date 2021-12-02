#pragma once
#include "Tile.h"
class DirtTile : public Tile
{
public:
	DirtTile();
	DirtTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~DirtTile();

	void Draw(aie::Renderer2D* pRenderer);
};

