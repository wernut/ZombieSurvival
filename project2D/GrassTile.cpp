#include "GrassTile.h"
#include "Tile.h"
#include "TextureManager.h"

GrassTile::GrassTile() : Tile(m_pTextureManager->TILE_GRASS)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
}

GrassTile::GrassTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_GRASS)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsSolid = false;
}

GrassTile::~GrassTile(){}