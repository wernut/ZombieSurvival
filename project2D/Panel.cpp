#include "Panel.h"
#include "Input.h"
#include <string>

Panel::Panel(Vector2 v2Pos, float fWidth, float fHeight, const char* pPanelName)
{
	m_pFont = new aie::Font("./font/consolas.ttf", 24);
	m_v2Position = v2Pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_bDrag = false;
	m_bMax = false;
	strcpy_s(szPanelName, pPanelName);
}

Panel::~Panel()
{
	delete m_pFont;
	m_pFont = nullptr;
}

void Panel::Update(float fDeltaTime)
{
	aie::Input* pInput = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = (float)pInput->GetMouseX();
	v2MousePos.y = (float)pInput->GetMouseY();

	if (pInput->WasMouseButtonPressed(0) && TopOfContainer(v2MousePos) && !InsideMaxBox(v2MousePos))
	{
		m_bDrag = true;
	}

	if (InsideMaxBox(v2MousePos) && pInput->WasMouseButtonPressed(0))
	{

		if (!m_bMax)
		{
			m_v2Position.y = m_v2Position.y + m_fHeight - 30.0f;
			m_fHeight = 30.0f;
			m_bMax = true;
		}
		else
		{
			m_v2Position.y = m_v2Position.y - 200.0f + 30.0f;
			m_fHeight = 200.0f;
			m_bMax = false;
		}

	}

	if (m_bDrag)
	{
		m_v2Position.x += pInput->GetMouseDeltaX();
		m_v2Position.y += pInput->GetMouseDeltaY();
	}

	if (pInput->WasMouseButtonReleased(0) && m_bDrag)
	{
		m_bDrag = false;
	}
}

void Panel::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->SetRenderColour(0.4f, 0.4f, 0.4f, 0.7f);
	// Draw box.
	pRenderer->DrawBox(m_v2Position.x + (m_fWidth / 2), m_v2Position.y + (m_fHeight / 2), m_fWidth, m_fHeight);
	// Draw line seperating containers.
	pRenderer->SetRenderColour(0.0f, 0.0f, 0.0f, 1.0f);
	pRenderer->DrawLine(m_v2Position.x, m_v2Position.y + m_fHeight - 30.0f, m_v2Position.x + m_fWidth, m_v2Position.y + m_fHeight - 30.0f);
	// Draw text.
	pRenderer->DrawText(m_pFont, szPanelName, m_v2Position.x + 2.0f, m_v2Position.y + m_fHeight - 24.0f);
	// Draw small box.
	if (!m_bMax)
		pRenderer->SetRenderColour(0.0f, 1.0f, 0.0f, 1.0f);
	else
		pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f, 1.0f);

	pRenderer->DrawBox(m_v2Position.x + m_fWidth - 15.0f, m_v2Position.y + m_fHeight - 15.0f, 15.0f, 15.0f);
	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}

bool Panel::IsInside(Vector2 v2MousePos, Vector2 v2Position, float fScale)
{
	return v2MousePos.x > v2Position.x - (fScale / 2) &&
		v2MousePos.x < v2Position.x + (fScale / 2) &&
		v2MousePos.y > v2Position.y - (fScale / 2) &&
		v2MousePos.y < v2Position.y + (fScale / 2);
}

bool Panel::IsInside(Vector2 v2MousePos)
{
	return v2MousePos.x > m_v2Position.x &&
		v2MousePos.x < m_v2Position.x + m_fWidth &&
		v2MousePos.y > m_v2Position.y &&
		v2MousePos.y < m_v2Position.y + m_fHeight;
}

bool Panel::TopOfContainer(Vector2 v2MousePos)
{
	return v2MousePos.x > m_v2Position.x &&
		v2MousePos.x < m_v2Position.x + m_fWidth &&
		v2MousePos.y > m_v2Position.y + m_fHeight - 30.0f &&
		v2MousePos.y < m_v2Position.y + m_fHeight;
}

bool Panel::InsideMaxBox(Vector2 v2MousePos)
{
	Vector2 v2Target(m_v2Position.x + m_fWidth - 15.0f, m_v2Position.y + m_fHeight - 15.0f);
	return IsInside(v2MousePos, v2Target, 15.0f);
}
