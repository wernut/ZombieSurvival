#pragma once
#include "Tile.h"

class CheckpointTile : public Tile
{
public:
	CheckpointTile();
	~CheckpointTile();

	void Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale);
};

