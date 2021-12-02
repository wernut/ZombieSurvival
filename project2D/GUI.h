#pragma once

#include "Renderer2D.h"
#include "Font.h"
#include "Player.h"

class GUI
{
private:
	GUI(Player* &pPlayer);
	static GUI* m_instance;
	Player* m_pPlayer;
	aie::Font* m_pFont;
	aie::Texture* m_pCursorTexture;
	float m_fRoundTimer;
	bool m_bRoundTimerState;
	int m_nRoundCount;
	float m_fRoundTimeInSeconds;

public:
	~GUI();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);

	void ToggleRoundTimer(bool bTimer);
	void ResetTimer();
	void SetRoundTimer(float fTime);
	void AddToRoundCount(int nCount);
	void SetRoundCount(int nCount);
	int GetRoundCount();
	float GetRoundTimer();


	static GUI* GetInstance() { return m_instance; }

	static void Create(Player* &pPlayer)
	{
		if (!m_instance)
			m_instance = new GUI(pPlayer);
	}

	static void Delete()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

