#include "UIButton.h"

UIButton::UIButton(const char* cButtonText, Vector2 v2Position, float fWidth, float fHeight)
{
	m_pApp = aie::Application::GetInstance();
	m_pInput = aie::Input::GetInstance();
	m_pButtonTexture = new aie::Texture("./textures/ui/button.png");
	m_pFont = new aie::Font("./font/ArcadeNormal.ttf", 24);
	m_pButtonText = cButtonText;
	m_v2Position = v2Position;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_bHasTexture = true;
	m_bIsEnabled = false;
	m_bIsHovering = false;
}

UIButton::UIButton(const char* cButtonText, Vector2 v2Position, float fWidth, float fHeight, Vector4 v4RGBA)
{
	m_pApp = aie::Application::GetInstance();
	m_pInput = aie::Input::GetInstance();
	m_pFont = new aie::Font("./font/ArcadeNormal.ttf", 24);
	m_pButtonText = cButtonText;
	m_v2Position = v2Position;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_v4RGBA = v4RGBA;
	m_bHasTexture = false;
	m_bIsEnabled = false;
	m_bIsHovering = false;
}

UIButton::~UIButton()
{
	if (m_bHasTexture)
	{
		delete m_pButtonTexture;
	}
	m_pButtonTexture = nullptr;

	delete m_pFont;
	m_pFont = nullptr;
}

void UIButton::Update(float fDeltaTime)
{

	if (InsideBounds(m_pInput->GetMouseX(), m_pInput->GetMouseY()))
	{
		m_bIsHovering = true;
		m_sIncreaseSize = 15;
		if (m_pInput->WasMouseButtonReleased(0))
		{
			m_bIsEnabled = true;
			m_sIncreaseSize = -2;
		}
	}
	else
	{
		m_bIsHovering = false;
	}
}

void UIButton::Draw(aie::Renderer2D* renderer)
{
	float fTextColor = 0.0f;
	if (m_bHasTexture)
	{
		if (m_bIsHovering)
		{
			renderer->DrawSprite(m_pButtonTexture, m_v2Position.x, m_v2Position.y, m_fWidth + m_sIncreaseSize, m_fHeight + m_sIncreaseSize);
			fTextColor = 1.0f;
		}
		else
		{
			renderer->DrawSprite(m_pButtonTexture, m_v2Position.x, m_v2Position.y, m_fWidth, m_fHeight);
			fTextColor = 0.0f;
		}
	}
	else
	{
		if (m_bIsHovering)
		{
			renderer->SetRenderColour(m_v4RGBA.x, m_v4RGBA.y, m_v4RGBA.z, 0.5f);
			renderer->DrawSprite(nullptr, m_v2Position.x, m_v2Position.y, m_fWidth + m_sIncreaseSize, m_fHeight + m_sIncreaseSize);
			fTextColor = 1.0f;
		}
		else
		{
			renderer->SetRenderColour(m_v4RGBA.x, m_v4RGBA.y, m_v4RGBA.z, 1.0f);
			renderer->DrawSprite(nullptr, m_v2Position.x, m_v2Position.y, m_fWidth, m_fHeight);
			fTextColor = 0.0f;
		}
	}

	renderer->SetRenderColour(fTextColor, fTextColor, fTextColor, 1.0f);
	renderer->DrawText(m_pFont, m_pButtonText, m_v2Position.x - (m_pFont->GetStringWidth(m_pButtonText) / 2), m_v2Position.y - 12);
	renderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}

bool UIButton::InsideBounds(int mouseX, int mouseY)
{
	return mouseX > m_v2Position.x - (m_fWidth / 2) && mouseX < m_v2Position.x + (m_fWidth / 2) &&
		mouseY > m_v2Position.y - (m_fHeight / 2) && mouseY < m_v2Position.y + (m_fHeight / 2);
}

bool UIButton::GetEnabled()
{
	return m_bIsEnabled;
}

void UIButton::SetEnabled(bool bEnabled)
{
	m_bIsEnabled = bEnabled;
}
