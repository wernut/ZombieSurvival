#pragma once
#include "State.h"
#include "Level.h"
#include "TexturePicker.h"

class CreatorState : public State
{
private:
	Level* m_pLevel;
	TexturePicker* m_pTexturePicker;
	Loader* m_pTileSaver;
	bool m_bIsSelecting;
	bool m_bCheckpointExists;
	Vector2 m_aSelectionPoints[2];
	void ChangeTileModulas(Tile* pSelected, int x, int y);
	int DetermineIterationType(Vector2 v2Start, Vector2 v2End);
	void SetSelectionPoint(int nIndex, Vector2 v2Position);
	void ChangeTileArea(Tile* &pSelected);

public:
	CreatorState(StateMachine* pStateMachine);
	virtual ~CreatorState();

	void ChangeTile(Tile* pSelected, Node* pNode);
	void OnEnter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnExit();
};

