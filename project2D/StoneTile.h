#pragma once
#include "Tile.h"
class StoneTile : public Tile
{
public:
	StoneTile();
	StoneTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~StoneTile();

	void Draw(aie::Renderer2D* pRenderer);
	void OnCollision(GameObject* pGameObject);
	bool IsSolid();
};

