#pragma once
#include "State.h"
#include "Renderer2D.h"

class StateMachine
{
public:
	enum ESTATE
	{
		ESTATE_MAINMENU,
		ESTATE_CREATOR,
		ESTATE_DEATHSCREEN,
		ESTATE_GAMEPAUSED,
		ESTATE_GAME,
		COUNT
	};
	StateMachine();
	~StateMachine();
	void SetState(ESTATE eState);
	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
private:
	ESTATE m_eCurrentState;
	State* m_stateList[COUNT];
};

