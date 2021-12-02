#pragma once
#include "State.h"
#include "Font.h"
#include "UIButton.h"

class MainMenuState : public State
{
private:
	aie::Font* m_pTitleFont;
	aie::Font* m_pFont;
	UIButton* m_pStartButton;
	UIButton* m_pExitButton;

public:

	MainMenuState(StateMachine* pStateMachine);
	virtual ~MainMenuState();

	void OnEnter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnExit();
};

