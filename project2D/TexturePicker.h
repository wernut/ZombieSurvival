#pragma once
#include "Renderer2D.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Font.h"
#include "Tile.h"
#include "Panel.h"

class TexturePicker : public Panel
{
private:
	Tile* m_pSelectedTile;
	int m_nSelectedTile;
	void DrawTextureBox(aie::Renderer2D* pRenderer, int eTexture, Vector2 v2Position);
public:
	TexturePicker();
	~TexturePicker();
	
	Tile* GetSelected();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
};

