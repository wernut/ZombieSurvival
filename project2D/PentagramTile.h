#pragma once
#include "Tile.h"
#include "StateMachine.h"

class PentagramTile : public Tile
{
private:

	enum EDRAWSTATE
	{
		EDRAWSTATE_IDLE,
		EDRAWSTATE_SPAWN,
		EDRAWSTATE_COUNT,
	};

	EDRAWSTATE m_eCurrentState;
public:

	PentagramTile();
	PentagramTile(Vector2 v2Position, int nIndexX, int nIndexY);
	~PentagramTile();
	void Draw(aie::Renderer2D* pRenderer, Vector2 v2Pos, Vector2 fScale);
	void Update(float fDeltaTime);
	void UpdateState(float fDeltaTime);
	void RotatePentagram(float fDeltaTime);
	};

