#pragma once
#include "Tile.h"
class TreeTile : public Tile
{
public:
	TreeTile();
	TreeTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~TreeTile();

	void Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale);
};

