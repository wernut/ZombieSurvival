#include "TextureManager.h"
#include "GrassTile.h"
#include "DirtTile.h"
#include "StoneTile.h"
#include "WoodPlankTile.h"
#include "WellTile.h"
#include "FlowerTile.h"
#include "CrateTile.h"
#include "PentagramTile.h"
#include "TreeTile.h"
#include "VoidTile.h"
#include "CheckpointTile.h"
#include <iostream>

TextureManager*::TextureManager::m_pInstance = nullptr;

TextureManager::TextureManager()
{
	m_rgTextures = new aie::Texture*[E_COUNT];
	LoadTextures();
}

TextureManager::~TextureManager()
{
	for (int i = 0; i < E_COUNT; ++i)
	{
		if(i != TILE_COUNT)
			delete m_rgTextures[i];
	}
	delete[] m_rgTextures;
}

void TextureManager::LoadTextures()
{
	// Entity sprites.
	m_rgTextures[ENTITY_PLAYER] = new aie::Texture("./textures/entities/player_move_animation.png");
	m_rgTextures[ENTITY_PLAYER_SHOOT] = new aie::Texture("./textures/entities/player_shoot_animation.png");
	m_rgTextures[ENTITY_ZOMBIE] = new aie::Texture("./textures/entities/zombie_animation.png");
	m_rgTextures[ENTITY_ZOMBIESPAWN] = new aie::Texture("./textures/entities/zombie_spawn_animation.png");
	m_rgTextures[ENTITY_ZOMBIEATTACK] = new aie::Texture("./textures/entities/zombie_attack_animation.png");
	m_rgTextures[TILE_ZOMBIESPAWN] = new aie::Texture("./textures/tiles/skull.png");
	m_rgTextures[PLAYER_HEART] = new aie::Texture("./textures/entities/heart.png");
	
	// Tile sprites.
	m_rgTextures[TILE_VOID] = nullptr;
	m_rgTextures[TILE_GRASS] = new aie::Texture("./textures/tiles/grass.png");
	m_rgTextures[TILE_DIRT] = new aie::Texture("./textures/tiles/dirt.png");
	m_rgTextures[TILE_STONE] = new aie::Texture("./textures/tiles/stone.png");
	m_rgTextures[TILE_WOODPLANK] = new aie::Texture("./textures/tiles/wood_plank.png");
	m_rgTextures[TILE_WELL] = new aie::Texture("./textures/tiles/well.png");
	m_rgTextures[TILE_FLOWER] = new aie::Texture("./textures/tiles/flower.png");
	m_rgTextures[TILE_CRATE] = new aie::Texture("./textures/tiles/crate.png");
	m_rgTextures[TILE_TREE] = new aie::Texture("./textures/tiles/tree.png");
	m_rgTextures[TILE_PENTAGRAM_ANIMATION] = new aie::Texture("./textures/entities/pentagram_spawn_animation_2.png");
	m_rgTextures[TILE_CHECKPOINT] = new aie::Texture("./textures/tiles/checkpoint.png");;
}

aie::Texture* TextureManager::GetTexture(E_TEXTURES nIndex)
{
	return m_rgTextures[nIndex];
}

aie::Texture* TextureManager::GetTexture(int nIndex)
{
	return m_rgTextures[nIndex];
}

/* Returns new tile from ID. Used for loading and saving files!*/
Tile* TextureManager::GetTileFromID(int nIndex)
{
	switch (nIndex)
	{
	case TILE_GRASS:
		return new GrassTile();
		break;

	case TILE_DIRT:
		return new DirtTile();
		break;

	case TILE_STONE:
		return new StoneTile();
		break;

	case TILE_WOODPLANK:
		return new WoodPlankTile();
		break;

	case TILE_WELL:
		return new WellTile();
		break;

	case TILE_FLOWER:
		return new FlowerTile();
		break;

	case TILE_CRATE:
		return new CrateTile();
		break;

	case TILE_PENTAGRAM_ANIMATION:
		return new PentagramTile();
		break;

	case TILE_TREE:
		return new TreeTile();
		break;

	case TILE_VOID:
		return new VoidTile();
		break;

	case TILE_CHECKPOINT:
		return new CheckpointTile();
		break;
	}

	return nullptr;
}