#pragma once
#include "State.h"
#include "Font.h"
#include "UIButton.h"

class GamePausedState : public State
{
private:
	aie::Font* m_pFont;
	UIButton* m_pMainMenuButton;
	UIButton* m_pExitButton;
	UIButton* m_pResumeButton;

public:
	GamePausedState(StateMachine* pStateMachine);
	virtual ~GamePausedState();

	void OnEnter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnExit();
};