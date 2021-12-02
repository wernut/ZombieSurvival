#pragma once
#include "Renderer2D.h"
class StateMachine;

class State
{
public:
	State(StateMachine* stateMachine) { m_pStateMachine = stateMachine; };
	virtual ~State() {}
	virtual void OnEnter() {}
	virtual void Update(float deltaTime) {}
	virtual void Draw(aie::Renderer2D* renderer) {}
	virtual void OnExit() {}

protected:
	StateMachine* m_pStateMachine;
};

