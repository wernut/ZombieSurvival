#pragma once
#include "Tile.h"
class VoidTile : public Tile
{
public:
	VoidTile();
	~VoidTile();

	void Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale);
};

