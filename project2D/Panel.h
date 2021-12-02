#pragma once
#include "Vector2.h"
#include "Font.h"
#include "Renderer2D.h"

class Panel
{
protected:
	Vector2 m_v2Position;
	float m_fWidth, m_fHeight;
	aie::Font* m_pFont;
	char szPanelName[64];
	bool m_bDrag;
	bool m_bMax;
	bool TopOfContainer(Vector2 v2MousePos);
	bool InsideMaxBox(Vector2 v2MousePos);

public:
	Panel(Vector2 v2Pos, float fWidth, float fHeight, const char* pName);
	~Panel();

	bool IsInside(Vector2 v2MousePos, Vector2 v2Target, float fScale);
	bool IsInside(Vector2 v2MousePos);

	virtual void Update(float fDeltaTime);
	virtual void Draw(aie::Renderer2D* pRenderer);
};

