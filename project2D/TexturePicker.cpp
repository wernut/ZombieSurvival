#include "TexturePicker.h"
#include "Application.h"
#include "Input.h"
#include "GrassTile.h"
#include "StoneTile.h"
#include "DirtTile.h"
#include "WellTile.h"
#include "WoodPlankTile.h"
#include "CrateTile.h"
#include "FlowerTile.h"
#include <iostream>

TexturePicker::TexturePicker() : Panel(Vector2(20, 500), 180.0f, 200.0f, "Tiles")
{
	m_pSelectedTile = nullptr;
	m_nSelectedTile = 0;
}

TexturePicker::~TexturePicker()
{
	if (m_pSelectedTile)
		delete m_pSelectedTile;
}

void TexturePicker::Update(float fDeltaTime)
{
	// Get the texture manager.
	TextureManager* pTextureManager = TextureManager::GetInstance();

	// Get window parameters.
	aie::Application* pApplication = aie::Application::GetInstance();
	float fWindowWidth = (float)pApplication->GetWindowWidth();
	float fWindowHeight = (float)pApplication->GetWindowHeight();

	aie::Input* pInput = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = (float) pInput->GetMouseX();
	v2MousePos.y = (float) pInput->GetMouseY();

	// Update base class.
	Panel::Update(fDeltaTime);

	// Check if the mouse has clicked a texture.
	if (!m_bMax)
	{
		Vector2 v2Position = m_v2Position;
		v2Position.x = m_v2Position.x + 22.5f;
		v2Position.y = v2Position.y + m_fHeight - 55.0f;
		if (pInput->WasMouseButtonReleased(0))
		{
			for (int i = pTextureManager->TILE_GRASS; i < pTextureManager->TILE_COUNT; ++i)
			{
				if (i == pTextureManager->TILE_WOODPLANK + 1 || i == pTextureManager->TILE_PENTAGRAM_ANIMATION + 1)
				{
					v2Position.y -= (SQUARE_SIZE + 5.0f);
					v2Position.x = m_v2Position.x + 22.5f;
				}

				if (IsInside(v2MousePos, v2Position, SQUARE_SIZE))
				{
					m_nSelectedTile = i;
					break;
				}

				v2Position.x += (SQUARE_SIZE + 5.0f);

			}
		}
	}
}

void TexturePicker::Draw(aie::Renderer2D* pRenderer)
{
	// Draw base class.
	Panel::Draw(pRenderer);

	// Get the texture manager.
	TextureManager* pTextureManager = TextureManager::GetInstance();

	// Get window parameters.
	aie::Application* pApplication = aie::Application::GetInstance();
	float fWindowWidth  = (float) pApplication->GetWindowWidth();
	float fWindowHeight = (float) pApplication->GetWindowHeight();

	if (!m_bMax)
	{
		Vector2 v2Position = m_v2Position;
		v2Position.x = m_v2Position.x - 22.5f;
		v2Position.y = v2Position.y + m_fHeight - 55.0f;
		// Draw textures.
		for (int i = pTextureManager->TILE_GRASS; i < pTextureManager->TILE_COUNT; ++i)
		{
			if (i == pTextureManager->TILE_WOODPLANK + 1 || i == pTextureManager->TILE_PENTAGRAM_ANIMATION + 1)
			{
				v2Position.y -= (SQUARE_SIZE + 5.0f);
				v2Position.x = m_v2Position.x - 22.5f;
			}
			v2Position.x += (SQUARE_SIZE + 5.0f);

			if (i == m_nSelectedTile)
				pRenderer->DrawBox(v2Position.x, v2Position.y, SQUARE_SIZE + 2.5f, SQUARE_SIZE + 2.5f);

			// Texture display.
			DrawTextureBox(pRenderer, i, v2Position);
		}
	}
}

void TexturePicker::DrawTextureBox(aie::Renderer2D* pRenderer, int eTexture, Vector2 v2Position)
{	
	// Get the texture manager.
	TextureManager* pTextureManager = TextureManager::GetInstance();
	if (eTexture == pTextureManager->TILE_PENTAGRAM_ANIMATION)
	{
		aie::Application* pApp = aie::Application::GetInstance();
		float time = pApp->GetTime();
		float animSpeed = 12.0f;
		int frame = ((int)(time * animSpeed) % 15);
		float size = 1.0f / 8.0f;
		pRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	}
	else if (eTexture == pTextureManager->TILE_VOID)
	{
		pRenderer->SetRenderColour(0.0f, 0.0f, 0.0f, 1.0f);
	}
	pRenderer->DrawSprite(pTextureManager->GetTexture(eTexture), v2Position.x, v2Position.y, SQUARE_SIZE, SQUARE_SIZE);
	pRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}

Tile* TexturePicker::GetSelected()
{
	TextureManager* pTextureManager = TextureManager::GetInstance();
	return pTextureManager->GetTileFromID(m_nSelectedTile);
}
