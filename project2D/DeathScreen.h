#pragma once
#include "State.h"
#include "Font.h"
#include "UIButton.h"

class DeathScreen : public State
{
private:
	aie::Font* m_pFont;
	UIButton* m_pMainMenuButton;
	UIButton* m_pExitButton;

public:
	DeathScreen(StateMachine* pStateMachine);
	virtual ~DeathScreen();

	void OnEnter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnExit();
};