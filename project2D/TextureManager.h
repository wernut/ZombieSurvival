#pragma once
#include "Texture.h"
#include "DynamicArray.h"
#include "Vector2.h"
#include "Renderer2D.h"

class Tile;

#define SQUARE_SIZE 40.0f

class TextureManager
{
public:

	enum E_TEXTURES
	{
		// ENTITIES
		ENTITY_PLAYER,
		ENTITY_PLAYER_SHOOT,
		ENTITY_ZOMBIE,
		ENTITY_ZOMBIESPAWN,
		TILE_ZOMBIESPAWN,
		
		// TILES
		TILE_GRASS,
		TILE_DIRT,
		TILE_STONE,
		TILE_WOODPLANK,
		TILE_WELL,
		TILE_FLOWER,
		TILE_CRATE,
		TILE_PENTAGRAM_ANIMATION,
		TILE_TREE,
		TILE_VOID,
		TILE_CHECKPOINT,
		TILE_COUNT,


		// ITEMS / OTHER
		PLAYER_HEART,
		ENTITY_ZOMBIEATTACK,

		// TOTAL COUNT
		E_COUNT,
	};

private:
	static TextureManager* m_pInstance;
	aie::Texture** m_rgTextures;

public:

	TextureManager();
	~TextureManager();

	aie::Texture* GetTexture(E_TEXTURES nIndex);
	aie::Texture* GetTexture(int nIndex);
	void LoadTextures();
	Tile* GetTileFromID(int nIndex);


	// Singleton functions.
	static void Create()
	{
		if (!m_pInstance)
			m_pInstance = new TextureManager();
	}

	static void Delete()
	{
		if (m_pInstance)
			delete m_pInstance;
	}

	static TextureManager* GetInstance() { return m_pInstance; }
};