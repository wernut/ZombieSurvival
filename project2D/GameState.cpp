#include "GameState.h"
#include "Level.h"
#include "Application.h"
#include "Grid.h"
#include "StateMachine.h"
#include "Input.h"
#include "Zombie.h"
#include "GUI.h"

GameState::GameState(StateMachine* pStateMachine) : State(pStateMachine)
{
	// Setting the background colour.
	aie::Application* app = aie::Application::GetInstance();
	app->SetBackgroundColour(0.2f, 0.2f, 0.2f, 1.0f);

	// Create the level.
	m_pLevel = new Level();

	// Create tile saver.
	m_pLoader = new Loader(32, 18);

	// Set the loaded boolean to false.
	m_bLoaded = false;

	// Setting the should be loaded bool to true to init the game.
	m_bShouldBeLoaded = true;

	// Create the player.
	m_pPlayer = new Player();
	m_pPlayer->SetParent(m_pLevel);

	// Create the gun.
	m_pGun = new Gun(m_pPlayer, m_pLevel);
	m_pGun->SetParent(m_pPlayer);

	// Create the GUI.
	GUI::Create(m_pPlayer);

	// !! CAUSING TWO MEMORY LEAKS.
	m_prgActiveEntities.SetShouldDelete(true);
	m_prgUnactiveEntities.SetShouldDelete(true);
}

GameState::~GameState()
{
	// Delete the level.
	delete m_pLevel;

	// Delete the tile saver.
	delete m_pLoader;

	// Delete the GUI.
	GUI::Delete();
}

void GameState::OnEnter() 
{
	aie::Application* app = aie::Application::GetInstance();
	app->SetShowCursor(false);

	if (m_bShouldBeLoaded)
	{
		// Creation of the level and all the objects.
		if (!m_bLoaded)
		{
			// Loading the level from the spawn file.
			Grid* pGrid = m_pLevel->GetGrid();
			Node*** aapNodeList = pGrid->GetNodeList();
			Vector2 v2PlayerSpawn = m_pLevel->GetPlayerSpawn();
			m_pLoader->Load(aapNodeList, v2PlayerSpawn, "./levels/spawn.LVL");
			m_pLevel->SetPlayerSpawn(v2PlayerSpawn);
			m_pLevel->UpdateSolidTiles(m_pLoader->GetSolidNodePos());
			pGrid->UpdateGrid();

			// Updating the solid node collision boxes.
			for (int i = 0; i < (int)m_pLoader->GetSolidNodePos().size(); ++i)
			{
				Vector2 v2Pos = m_pLoader->GetSolidNodeIndex(i);
				Node* pNode = m_pLevel->GetGrid()->GetNodeByPosition(v2Pos);

				m_pLevel->GetGrid()->CheckSolidNeighbours(pNode);
			}

			// Player.
			m_pPlayer->SetPosition(m_pLevel->GetPlayerSpawn());
			m_pPlayer->SetRotation(10.0f);
			m_prgActiveEntities.PushBack(m_pPlayer);
			m_nZombieCount = 0;

			// Creating the gun.
			float offset = 16.0f;
			m_pGun->SetPosition(Vector2(offset - 2.0f, offset - 40.0f));

			// Setting the player's current weapon;
			m_pPlayer->SetCurrentWeapon(m_pGun);

			// Add player to collision manager.
			CollisionManager* pCM = CollisionManager::GetInstance();
			pCM->AddCollider(m_prgActiveEntities[0]);

			// Create zombies.
			for (int i = 0; i < (int)m_pLoader->GetZombieSpawnPos().size(); ++i)
			{
				Vector2 v2Spawn = m_pLoader->GetZombieSpawnIndex(i);
				CreateZombie(v2Spawn);
			}

			m_bLoaded = true;
		}
		else
		{
			// Set the player active.
			m_prgActiveEntities.PushFront(m_pPlayer);
			m_prgUnactiveEntities.Remove(m_pPlayer);

			// Reset player properties.
			m_pPlayer->SetPosition(m_pLevel->GetPlayerSpawn());
			m_pPlayer->SetHealth(10);
			m_pPlayer->SetAlive(true);
			m_pPlayer->SetScore(0);
			m_pPlayer->SetActive(true);

			// Reset the round properties.
			m_pGun->Refill();
			m_nZombieCount = 0;
			GUI::GetInstance()->SetRoundCount(0);
			GUI::GetInstance()->ResetTimer();
		}
	}
}

Zombie* GameState::CreateZombie(Vector2 v2Spawn)
{
	CollisionManager* pCM = CollisionManager::GetInstance();
	Zombie* pZombie = new Zombie(m_pLevel->GetGrid(), m_pPlayer);
	pZombie->SetParent(m_pLevel);
	pZombie->SetSpawnPosition(v2Spawn);
	pZombie->SetAlive(false);

	pCM->AddHitbox(pZombie);
	pCM->AddCollider(pZombie);
	m_prgUnactiveEntities.PushBack(pZombie);

	return pZombie;
}

void GameState::SpawnZombies()
{
	CollisionManager* pCM = CollisionManager::GetInstance();

	m_nZombieCount += m_prgUnactiveEntities.GetSize();
 	for (int i = 0; i < m_nZombieCount; ++i)
	{
		Zombie* pZombie = (Zombie*) m_prgUnactiveEntities[i];
		Vector2 v2Spawn = pZombie->GetSpawnPosition();
		pZombie->SetAlive(true);
		m_prgActiveEntities.PushBack(pZombie);
	}

	m_prgUnactiveEntities.Clear();
}

void GameState::Update(float fDeltaTime) 
{
	// Updating collision manager.
	CollisionManager* pCM = CollisionManager::GetInstance();
	pCM->Update(fDeltaTime);

	// Update the GUI.
	GUI* gui = GUI::GetInstance();
	gui->Update(fDeltaTime);

	// Spawning the zombies when the round timer hits 0.
	if (gui->GetRoundTimer() <= 0.0f)
	{
		SpawnZombies();
		gui->ResetTimer();
		gui->AddToRoundCount(1);

		if (gui->GetRoundCount() > 1)
		{
			CreateZombieSpawnTile();
		}
	}

	// If all the zombies are dead, then restart the timer.
	if (m_nZombieCount == 0)
	{
		gui->ToggleRoundTimer(true);
	}

	// Update the level and the global transformation matrix.
	m_pLevel->Update(fDeltaTime);
	m_pLevel->UpdateGlobalTransform();


	// Checking if the zombie is alive.
	for (int i = 1; i < m_prgActiveEntities.GetSize(); ++i)
	{
		if (m_prgActiveEntities[i]->GetHealth() <= 0)
		{
			Entity* pZombie = m_prgActiveEntities[i];
			pZombie->SetAlive(false);
			m_prgUnactiveEntities.PushBack(pZombie);
			m_prgActiveEntities.Erase(i);
			--m_nZombieCount;
			m_pPlayer->SetScore(m_pPlayer->GetScore() + 10);
		}
	}

	// Checking if player is alive.
	if (m_pPlayer->GetHealth() <= 0)
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_DEATHSCREEN);
	
	aie::Input* pInput = aie::Input::GetInstance();
	if (pInput->WasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		this->m_bShouldBeLoaded = false;
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAMEPAUSED);
	}
}

void GameState::Draw(aie::Renderer2D* pRenderer) 
{
	// Draw level.
	m_pLevel->Draw(pRenderer);

	// Draw the GUI.
	GUI* gui = GUI::GetInstance();
	gui->Draw(pRenderer);
}

void GameState::OnExit() 
{
	if (m_bShouldBeLoaded)
	{
		// Swapping all the entitie's to the unactive list.
		m_prgUnactiveEntities.PushFront(m_pPlayer);
		m_prgActiveEntities.Remove(m_pPlayer);

		int nZombieCount = m_prgActiveEntities.GetSize();
		for (int i = 0; i < nZombieCount; ++i)
		{
			Entity* pZombie = m_prgActiveEntities[i];
			pZombie->SetAlive(false);
			m_prgUnactiveEntities.PushBack(pZombie);
		}

		m_prgActiveEntities.Clear();
		m_nZombieCount = 0;
	}
}

void GameState::CreateZombieSpawnTile()
{
	TextureManager* pTM = TextureManager::GetInstance();

	Node* pNode = m_pLevel->GetGrid()->GetRandomNode();
	Tile* pSelected = pTM->GetTileFromID(pTM->TILE_PENTAGRAM_ANIMATION);
	Tile* pTargetTile = pNode->m_pTile;

	// Place tile without deleting underlying texture.
	pNode->m_pTile = pSelected;
	pNode->m_pTile->SetOverlayTexture(pTargetTile->GetETexture());
	delete pTargetTile;

	Vector2 v2Spawn = pNode->m_v2Position;
	CreateAndSpawnZombie(v2Spawn);
}

void GameState::CreateAndSpawnZombie(Vector2 v2Spawn)
{
	Zombie* pZombie = CreateZombie(v2Spawn);
	pZombie->SetAlive(true);
	m_prgActiveEntities.PushBack(pZombie);
	m_prgUnactiveEntities.Remove(pZombie);
}
