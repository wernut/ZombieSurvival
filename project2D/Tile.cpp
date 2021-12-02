#include "Tile.h"
#include "TextureManager.h"

Tile::Tile() : GameObject("Tile")
{
	m_pTextureManager = TextureManager::GetInstance();
	m_pTexture = nullptr;
	m_pOverlayTexture = nullptr;
	m_nOverlayTexture = -1;
	m_nTexture = 0;
	m_fSize = 30.0f;
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsSolid = false;
	m_bIsTransparent = false;
	m_fLightValue = 1.0f;
	m_bIsOffset = false;
}

Tile::Tile(TextureManager::E_TEXTURES eTexture) : GameObject("Tile")
{
	m_pTextureManager = TextureManager::GetInstance();
	m_pTexture = m_pTextureManager->GetTexture(eTexture);
	m_pOverlayTexture = nullptr;
	m_nOverlayTexture = -1;
	m_nTexture = eTexture;
	m_fSize = 30.0f;
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsSolid = false;
	m_bIsTransparent = false;
	m_fLightValue = 1.0f;
	m_bIsOffset = false;
}

Tile::Tile(TextureManager::E_TEXTURES eTexture, bool bIsSolid) : GameObject("Tile")
{
	m_pTextureManager = TextureManager::GetInstance();
	m_pTexture = m_pTextureManager->GetTexture(eTexture);
	m_pOverlayTexture = nullptr;
	m_nOverlayTexture = -1;
	m_nTexture = eTexture;
	m_fSize = 30.0f;
	m_nIndexX = 0;
	m_nIndexY = 0;
	m_bIsSolid = bIsSolid;
	m_bIsTransparent = false;
	m_fLightValue = 1.0f;
	m_bIsOffset = false;

	if (m_bIsSolid)
		m_rBounds = new Rectangle(m_v2Position.x, m_v2Position.y, SQUARE_SIZE, SQUARE_SIZE);
}

Tile::~Tile(){}

void Tile::Update(float fDeltaTime)
{
	GameObject::Update(fDeltaTime);
}

void Tile::Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale)
{
	pRenderer->SetRenderColour(m_fLightValue, m_fLightValue, m_fLightValue, 1.0f);

	if (m_pOverlayTexture)
	{
		if (m_bIsOffset)
		{
			pRenderer->DrawSprite(m_pOverlayTexture, m_v2LayerPosition.x, m_v2LayerPosition.y, m_v2LayerScale.x, m_v2LayerScale.y);
		}
		else
			pRenderer->DrawSprite(m_pOverlayTexture, v2Pos.x, v2Pos.y, fScale.x, fScale.y);
	}

	if(m_pTexture)
		pRenderer->DrawSprite(m_pTexture, v2Pos.x, v2Pos.y, fScale.x, fScale.y);

	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	//if (m_rBounds)
	//	m_rBounds->Draw(pRenderer, 1.0f, 0.0f, 0.0f, 0.5f);
}

aie::Texture* Tile::GetTexture()
{
	return m_pTexture;
}

void Tile::SetOverlayTexture(int eTexture)
{
	m_nOverlayTexture = eTexture;
	m_pOverlayTexture = m_pTextureManager->GetTexture(eTexture);
}

aie::Texture* Tile::GetOverlayTexture()
{
	return m_pOverlayTexture;
}

bool Tile::IsSolid()
{
	return m_bIsSolid;
}

int Tile::GetETexture()
{
	return m_nTexture;
}

int Tile::GetOverlayETexture()
{
	return m_nOverlayTexture;
}

bool Tile::IsTransparent()
{
	return m_bIsTransparent;
}

void Tile::SetLightValue(float fValue)
{
	m_fLightValue = fValue;
}

void Tile::UpdatePositionAndBounds(Vector2 v2Position)
{
	m_v2Position = v2Position;
	m_rBounds->m_x = v2Position.x;
	m_rBounds->m_y = v2Position.y;
}

