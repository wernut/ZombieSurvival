#include "WellTile.h"
#include "Tile.h"
#include "TextureManager.h"

WellTile::WellTile() : Tile(m_pTextureManager->TILE_WELL, true)
{
	m_bIsTransparent = true;
}

WellTile::WellTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_WELL, true)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsTransparent = true;
}

WellTile::~WellTile() {}

bool WellTile::IsSolid()
{
	return true;
}