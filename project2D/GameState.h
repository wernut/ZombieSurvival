#pragma once
#include "State.h"
#include "Renderer2D.h"
#include "DynamicArray.h"
#include "Entity.h"
#include "TileSaver.h"
#include "Player.h"
#include "Gun.h"
#include "Zombie.h"

#include <vector>

class Level;
class StateMachine;

class GameState : public State
{
private:
	Level* m_pLevel;
	Loader* m_pLoader;
	Player* m_pPlayer;
	Gun* m_pGun;
	DynamicArray<Entity*> m_prgActiveEntities;
	DynamicArray<Entity*> m_prgUnactiveEntities;
	int m_nZombieCount;
	bool m_bLoaded, m_bShouldBeLoaded;

	Zombie* CreateZombie(Vector2 v2Spawn);
	void CreateAndSpawnZombie(Vector2 v2Spawn);
	void CreateZombieSpawnTile();

public:

	// Class functions.
	GameState(StateMachine* pStateMachine);
	virtual ~GameState();

	void SpawnZombies();
	// State functions.
	void OnEnter();
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnExit();
};



