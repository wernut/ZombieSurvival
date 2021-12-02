#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "GameObject.h"
#include "TextureManager.h"


class Tile : public GameObject
{
protected:
	bool m_bIsSolid;
	bool m_bIsTransparent;
	aie::Texture* m_pTexture;
	aie::Texture* m_pOverlayTexture;
	float m_fSize;
	TextureManager* m_pTextureManager;
	int m_nIndexX, m_nIndexY;
	int m_nTexture;
	int m_nOverlayTexture;
	float m_fLightValue;
	bool m_bIsOffset;
	Vector2 m_v2LayerPosition, m_v2LayerScale;

public:
	Tile();
	Tile(TextureManager::E_TEXTURES);
	Tile(TextureManager::E_TEXTURES, bool bIsSolid);
	virtual ~Tile();
	virtual void Update(float fDeltaTime);
	virtual void Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale);
	int GetETexture();
	aie::Texture* GetTexture();
	int GetOverlayETexture();
	void SetOverlayTexture(int eTexture);
	aie::Texture* GetOverlayTexture();
	Vector2 m_v2Position;
	virtual bool IsSolid();
	virtual bool IsTransparent();
	void SetLightValue(float fValue);
	void UpdatePositionAndBounds(Vector2 v2Position);
};

