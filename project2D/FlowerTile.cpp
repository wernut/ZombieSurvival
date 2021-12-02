#include "FlowerTile.h"
#include "Tile.h"
#include "TextureManager.h"

FlowerTile::FlowerTile() : Tile(m_pTextureManager->TILE_FLOWER)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsTransparent = true;
}

FlowerTile::FlowerTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_FLOWER)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsSolid = false;
	m_bIsTransparent = true;
}

FlowerTile::~FlowerTile() {}