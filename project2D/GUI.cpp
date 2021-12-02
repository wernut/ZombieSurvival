#include "GUI.h"
#include "TextureManager.h"
#include "Application.h"
#include "Input.h"

GUI* GUI::m_instance = nullptr;

GUI::GUI(Player* &pPlayer)
{
	m_pPlayer = pPlayer;
	m_pFont = new aie::Font("./font/ArcadeNormal.ttf", 18);
	m_pCursorTexture = new aie::Texture("./textures/cursor.png");
	m_fRoundTimeInSeconds = 5.5f;
	m_fRoundTimer = m_fRoundTimeInSeconds;
	m_bRoundTimerState = true;
	m_nRoundCount = false;
}

GUI::~GUI()
{
	delete m_pFont;

	// Delete the cursor texture.
	delete m_pCursorTexture;

}

void GUI::Update(float fDeltaTime)
{
	if (m_bRoundTimerState)
	{
		m_fRoundTimer -= fDeltaTime;
	}
}

void GUI::Draw(aie::Renderer2D* pRenderer)
{
	// Get some instances.
	TextureManager* pTM = TextureManager::GetInstance();
	aie::Application* pApp = aie::Application::GetInstance();
	aie::Input* pInput = aie::Input::GetInstance();

	// Draw inventory.
	m_pPlayer->GetInventory()->Draw(pRenderer);

	// Draw health.
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();
	Vector2 v2Pos(24, fWindowHeight - 24);
	float size = 40.0f;

	for (int i = 0; i < m_pPlayer->GetHealth(); ++i)
	{
		pRenderer->DrawSprite(pTM->GetTexture(pTM->PLAYER_HEART), v2Pos.x, v2Pos.y, size, size);
		v2Pos.x += size;
	}

	// Draw ammo count.
	char ammo[32];
	sprintf_s(ammo, 32, "Ammo:%i/%i", m_pPlayer->GetCurrentWeapon()->GetClipSize(), m_pPlayer->GetCurrentWeapon()->GetAmmoCount());
	pRenderer->DrawText(m_pFont, ammo, 14.0f, fWindowHeight - 64.0f);

	// Draw score count.
	char score[32];
	sprintf_s(score, 32, "Score:%i", m_pPlayer->GetScore());
	pRenderer->DrawText(m_pFont, score, 14.0f, fWindowHeight - 86.0f);

	// Drawing the FPS.
	char fps[32];
	sprintf_s(fps, 32, "FPS:%i", pApp->GetFPS());
	pRenderer->DrawText(m_pFont, fps, fWindowWidth - 114.0f, fWindowHeight - 24.0f);

	// Drawing the round timer.
	char roundTimer[32];
	sprintf_s(roundTimer, 32, "Next round in:%i", (int)m_fRoundTimer);
	pRenderer->DrawText(m_pFont, roundTimer, (fWindowWidth / 2) - ((m_pFont->GetStringWidth(roundTimer) / 2)), fWindowHeight - 24.0f);

	// Drawing the round count.
	char roundCount[32];
	sprintf_s(roundCount, 32, "Round %i", m_nRoundCount);
	pRenderer->DrawText(m_pFont, roundCount, (fWindowWidth / 2) - ((m_pFont->GetStringWidth(roundCount) / 2)), fWindowHeight - 46.0f);
}

void GUI::SetRoundTimer(float fTime)
{
	m_fRoundTimer = fTime;
}

float GUI::GetRoundTimer()
{
	return m_fRoundTimer;
}

void GUI::ToggleRoundTimer(bool bTimer)
{
	m_bRoundTimerState = bTimer;
}

void GUI::ResetTimer()
{
	m_bRoundTimerState = false;
	m_fRoundTimer = m_fRoundTimeInSeconds;
}

void GUI::AddToRoundCount(int nCount)
{
	this->m_nRoundCount += nCount;
}

void GUI::SetRoundCount(int nCount)
{
	m_nRoundCount = nCount;
}

int GUI::GetRoundCount()
{
	return m_nRoundCount;
}
