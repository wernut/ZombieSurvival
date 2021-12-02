#include "StateMachine.h"
#include "CreatorState.h"
#include "GameState.h"
#include "DeathScreen.h"
#include "MainMenuState.h"
#include "GamePausedState.h"

StateMachine::StateMachine()
{
	// Creating the states of the game.
	m_stateList[ESTATE_MAINMENU] = new MainMenuState(this);
	m_stateList[ESTATE_CREATOR] = new CreatorState(this);
	m_stateList[ESTATE_DEATHSCREEN] = new DeathScreen(this);
	m_stateList[ESTATE_GAMEPAUSED] = new GamePausedState(this);
	m_stateList[ESTATE_GAME] = new GameState(this);

	m_eCurrentState = (ESTATE) -1;
	SetState(ESTATE_MAINMENU);
}

StateMachine::~StateMachine()
{
	for (int i = 0; i < COUNT; ++i)
	{
		State* pState = m_stateList[i];
		delete m_stateList[i];
	}
}

void StateMachine::SetState(ESTATE eState)
{
	if(m_eCurrentState > -1)
		m_stateList[m_eCurrentState]->OnExit();

	m_eCurrentState = eState;

	m_stateList[m_eCurrentState]->OnEnter();
}

void StateMachine::Update(float deltaTime)
{
	m_stateList[m_eCurrentState]->Update(deltaTime);
}

void StateMachine::Draw(aie::Renderer2D* renderer)
{
	m_stateList[m_eCurrentState]->Draw(renderer);
}
