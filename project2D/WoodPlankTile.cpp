#include "WoodPlankTile.h"
#include "Tile.h"
#include "TextureManager.h"

WoodPlankTile::WoodPlankTile() : Tile(m_pTextureManager->TILE_WOODPLANK)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsSolid = false;
}

WoodPlankTile::WoodPlankTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_WOODPLANK)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsSolid = false;
}


WoodPlankTile::~WoodPlankTile() {}
