#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Application.h"
#include "Input.h"
#include "Vector2.h"
#include "Vector4.h"
#include "GameObject.h"

class UIButton
{
private:
	Vector2 m_v2Position;
	float m_fWidth, m_fHeight;
	float m_sIncreaseSize;
	bool m_bIsEnabled;
	bool m_bIsHovering;
	bool m_bHasTexture;
	Vector4 m_v4RGBA;
	const char* m_pButtonText;

	aie::Texture*		m_pButtonTexture;
	aie::Application*	m_pApp;
	aie::Font*          m_pFont;
	aie::Input*			m_pInput;
public:
	UIButton(const char* cButtonText, Vector2 v2Position, float fWidth, float fHeight);
	UIButton(const char* cButtonText, Vector2 v2Position, float fWidth, float fHeight, Vector4 v4RGBA);
	~UIButton();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	bool InsideBounds(int x, int y);
	bool GetEnabled();
	void SetEnabled(bool bEnabled);
};
