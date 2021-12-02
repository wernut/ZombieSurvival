#include "CrateTile.h"

CrateTile::CrateTile() : Tile(m_pTextureManager->TILE_CRATE, true)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsTransparent = true;
}

CrateTile::CrateTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_CRATE, true)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsTransparent = true;
}

CrateTile::~CrateTile()
{
}
