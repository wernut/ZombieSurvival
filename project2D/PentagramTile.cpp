#include "PentagramTile.h"
#include "Application.h"

PentagramTile::PentagramTile() : Tile(m_pTextureManager->TILE_PENTAGRAM_ANIMATION, false)
{
	m_bIsTransparent = true;
	m_eCurrentState = EDRAWSTATE_SPAWN;
}

PentagramTile::PentagramTile(Vector2 v2Position, int nIndexX, int nIndexY) : Tile(m_pTextureManager->TILE_PENTAGRAM_ANIMATION, false)
{
	m_v2Position = v2Position;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_bIsTransparent = true;
	m_eCurrentState = EDRAWSTATE_SPAWN;
}

PentagramTile::~PentagramTile(){}

void PentagramTile::Update(float fDeltaTime)
{
	UpdateState(fDeltaTime);

	Tile::Update(fDeltaTime);
}


void PentagramTile::UpdateState(float fDeltaTime)
{
	switch (m_eCurrentState)
	{
	case EDRAWSTATE_SPAWN:
		UpdateState(fDeltaTime);
		break;
	}
}

void PentagramTile::RotatePentagram(float fDeltaTime)
{
	float fRotation = GetRotation();
	fRotation += 10.0f * fDeltaTime;
	SetRotation(fRotation);
}

void PentagramTile::Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale)
{
	Vector2 v2Scale(50.0f, 50.0f);
	Vector2 v2Position(v2Pos.x, v2Pos.y);
	float fRotation = GetRotation();
	fRotation += 5.0f;
	SetPosition(v2Position);
	SetRotation(fRotation);
	pRenderer->DrawSprite(m_pOverlayTexture, v2Pos.x, v2Pos.y, fScale.x, fScale.y);

	aie::Application* pApp = aie::Application::GetInstance();
	float time = pApp->GetTime();
	float animSpeed = 12.0f;
	int frame = ((int)(time * animSpeed) % 15);
	float size = 1.0f / 8.0f;
	pRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	pRenderer->DrawSpriteTransformed3x3(m_pTexture, GetGlobalTransform(), v2Scale.x, v2Scale.y);
	pRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
}
