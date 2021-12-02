#include "CheckpointTile.h"

/* Description:
			   A tile that will be used to create a location where the player will spawn.
			   This will be an overlay tile with no collision and not visible during the game play.
*/

CheckpointTile::CheckpointTile() : Tile(m_pTextureManager->TILE_CHECKPOINT)
{
	this->m_bIsTransparent = true;
}

CheckpointTile::~CheckpointTile() {}


void CheckpointTile::Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale)
{
	Vector2 v2Scale(55.0f, 50.0f);
	Vector2 v2Position(v2Pos.x, v2Pos.y);
	SetPosition(v2Position);

	if(m_pOverlayTexture)
		pRenderer->DrawSprite(m_pOverlayTexture, v2Pos.x, v2Pos.y, fScale.x, fScale.y);

	if(m_pTexture)
		pRenderer->DrawSpriteTransformed3x3(m_pTexture, GetGlobalTransform(), v2Scale.x, v2Scale.y);
}
