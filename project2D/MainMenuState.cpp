#include "MainMenuState.h"
#include "Application.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "Input.h"

MainMenuState::MainMenuState(StateMachine* pStateMachine) : State(pStateMachine)
{
	m_pTitleFont = new aie::Font("./font/ArcadeNormal.ttf", 56);
	m_pFont = new aie::Font("./font/ArcadeNormal.ttf", 16);

	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();

	Vector2 v2StartButtonPos(fWindowWidth / 2, fWindowHeight / 2 + 60);
	m_pStartButton = new UIButton("Start Game", v2StartButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	Vector2 v2ExitButtonPos(fWindowWidth / 2, fWindowHeight / 2 - 60);
	m_pExitButton = new UIButton("Exit Game", v2ExitButtonPos, 300, 100, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

MainMenuState::~MainMenuState()
{
	delete m_pTitleFont;
	delete m_pStartButton;
	delete m_pExitButton;
	delete m_pFont;
}

void MainMenuState::OnEnter() {}

void MainMenuState::Update(float fDeltaTime)
{
	m_pStartButton->Update(fDeltaTime);
	m_pExitButton->Update(fDeltaTime);

	if (m_pStartButton->GetEnabled())
	{
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
		m_pStartButton->SetEnabled(false);
	} else 	if (m_pExitButton->GetEnabled())
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	aie::Input* input = aie::Input::GetInstance();
	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
}

void MainMenuState::Draw(aie::Renderer2D* pRenderer)
{
	aie::Application* pApp = aie::Application::GetInstance();
	float fWindowWidth = (float)pApp->GetWindowWidth();
	float fWindowHeight = (float)pApp->GetWindowHeight();

	// TITLE
	pRenderer->DrawText(m_pTitleFont, "Zombie Survival", (fWindowWidth / 2) - (m_pTitleFont->GetStringWidth("Zombie Survival") / 2), fWindowHeight - 142.0f);

	// CONTROLS
	pRenderer->DrawText(m_pFont, "CONTROLS: ", 16, fWindowHeight - 262.0f);
	pRenderer->DrawText(m_pFont, "W - Move forwards ", 16, fWindowHeight - 278.0f);
	pRenderer->DrawText(m_pFont, "S - Move backwards ", 16, fWindowHeight - 294.0f);
	pRenderer->DrawText(m_pFont, "A - Rotate left ", 16, fWindowHeight - 310.0f);
	pRenderer->DrawText(m_pFont, "D - Rotate right ", 16, fWindowHeight - 326.0f);
	pRenderer->DrawText(m_pFont, "SPACE - Shoot ", 16, fWindowHeight - 342.0f);
	pRenderer->DrawText(m_pFont, "1 - Zombie Path", 16, fWindowHeight - 358.0f);

	const char* text = "Stay alive as long as you can! No health regen here... ";

	pRenderer->DrawText(m_pFont, text, (fWindowWidth / 2) - (m_pFont->GetStringWidth(text) / 2), 16.0f);


	m_pStartButton->Draw(pRenderer);
	m_pExitButton->Draw(pRenderer);
}

void MainMenuState::OnExit() {}
