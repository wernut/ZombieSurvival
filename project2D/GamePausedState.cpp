#include "GamePausedState.h"
#include "Application.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "Input.h"

GamePausedState::GamePausedState(StateMachine* pStateMachine) : State(pStateMachine)
{
	m_pFont = new aie::Font("./font/consolas_bold.ttf", 24);

	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();

	Vector2 v2ResumeButtonPos(fWindowWidth / 2, fWindowHeight / 2 + 120);
	m_pResumeButton = new UIButton("Resume Game", v2ResumeButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	Vector2 v2MainMenuButtonPos(fWindowWidth / 2, fWindowHeight / 2);
	m_pMainMenuButton = new UIButton("Main Menu", v2MainMenuButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	Vector2 v2ExitButtonPos(fWindowWidth / 2, fWindowHeight / 2 - 120);
	m_pExitButton = new UIButton("Exit Game", v2ExitButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

GamePausedState::~GamePausedState()
{
}

void GamePausedState::OnEnter()
{
	aie::Application* pApp = aie::Application::GetInstance();
	pApp->SetShowCursor(true);
}

void GamePausedState::Update(float fDeltaTime)
{
	m_pResumeButton->Update(fDeltaTime);
	m_pMainMenuButton->Update(fDeltaTime);
	m_pExitButton->Update(fDeltaTime);

	if (m_pResumeButton->GetEnabled())
	{
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
		m_pResumeButton->SetEnabled(false);
	}
	else if (m_pMainMenuButton->GetEnabled())
	{
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_MAINMENU);
		m_pMainMenuButton->SetEnabled(false);
	}
	else if (m_pExitButton->GetEnabled())
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	aie::Input* input = aie::Input::GetInstance();
	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
}

void GamePausedState::Draw(aie::Renderer2D* pRenderer)
{
	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();
	m_pMainMenuButton->Draw(pRenderer);
	m_pExitButton->Draw(pRenderer);
	m_pResumeButton->Draw(pRenderer);
}

void GamePausedState::OnExit() {}
