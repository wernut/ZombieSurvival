#include "DeathScreen.h"
#include "Application.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "Input.h"

DeathScreen::DeathScreen(StateMachine* pStateMachine) : State(pStateMachine)
{
	m_pFont = new aie::Font("./font/consolas_bold.ttf", 24);

	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();

	Vector2 v2MainMenuButtonPos(fWindowWidth / 2, fWindowHeight / 2 + 60);
	m_pMainMenuButton = new UIButton("Main Menu", v2MainMenuButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	Vector2 v2ExitButtonPos(fWindowWidth / 2, fWindowHeight / 2 - 60);
	m_pExitButton = new UIButton("Exit Game", v2ExitButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

DeathScreen::~DeathScreen()
{
	delete m_pFont;

	delete m_pMainMenuButton;
	delete m_pExitButton;
}

void DeathScreen::OnEnter() 
{
	aie::Application* pApp = aie::Application::GetInstance();
	pApp->SetShowCursor(true);
}

void DeathScreen::Update(float fDeltaTime)
{
	m_pMainMenuButton->Update(fDeltaTime);
	m_pExitButton->Update(fDeltaTime);

	if (m_pMainMenuButton->GetEnabled())
	{
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_MAINMENU);
		m_pMainMenuButton->SetEnabled(false);
	}
	else 	if (m_pExitButton->GetEnabled())
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	aie::Input* input = aie::Input::GetInstance();
	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
}

void DeathScreen::Draw(aie::Renderer2D* pRenderer)
{
	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();
	m_pMainMenuButton->Draw(pRenderer);
	m_pExitButton->Draw(pRenderer);
}

void DeathScreen::OnExit() {}
