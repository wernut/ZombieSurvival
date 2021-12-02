#include "TreeTile.h"
#include "Tile.h"
#include "TextureManager.h"

TreeTile::TreeTile() : Tile(m_pTextureManager->TILE_TREE, false)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsTransparent = true;
	m_bIsOffset = true;
	m_v2LayerPosition = this->GetPosition();
	m_v2LayerScale = Vector2(40.0f, 40.0f);
}

TreeTile::TreeTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_TREE, false)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsTransparent = true;
	m_bIsOffset = true;
	m_v2LayerPosition = v2Position;
	m_v2LayerScale = Vector2(40.0f, 40.0f);
}

TreeTile::~TreeTile() {}


void TreeTile::Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale)
{
	m_v2LayerPosition = v2Pos;
	Vector2 v2Scale(50.0f, 100.0f);
	Vector2 v2Position(v2Pos.x, v2Pos.y - 40.0f);
	Tile::Draw(pRenderer, v2Position, v2Scale);
}