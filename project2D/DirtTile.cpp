#include "DirtTile.h"

DirtTile::DirtTile() : Tile(m_pTextureManager->TILE_DIRT)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsSolid = false;
}

DirtTile::DirtTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_DIRT)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsSolid = false;
}
DirtTile::~DirtTile()
{}


void DirtTile::Draw(aie::Renderer2D* pRenderer) {}
