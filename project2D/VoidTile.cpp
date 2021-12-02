#include "VoidTile.h"

VoidTile::VoidTile() : Tile(m_pTextureManager->TILE_VOID, true)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
}

VoidTile::~VoidTile(){}

void VoidTile::Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale)
{
	pRenderer->SetRenderColour(0.0f, 0.0f, 0.0f, 1.0f);
	pRenderer->DrawSprite(m_pTexture, v2Pos.x, v2Pos.y, fScale.x, fScale.y);
	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}
