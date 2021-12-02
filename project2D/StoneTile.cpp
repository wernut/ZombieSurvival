#include "StoneTile.h"
#include "Tile.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <iostream>

StoneTile::StoneTile() : Tile(m_pTextureManager->TILE_STONE, true)
{
	m_nIndexX = 0;
	m_nIndexY = 0;
}

StoneTile::StoneTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_STONE, true)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
}

StoneTile::~StoneTile() {}

void StoneTile::Draw(aie::Renderer2D* pRenderer) {}

void StoneTile::OnCollision(GameObject* pGameObject)
{} 

bool StoneTile::IsSolid()
{
	return true;
}