#include "Level.h"
#include "Application.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Input.h"
#include "Node.h"
#include <random>
#include <iostream>

Level::Level() : GameObject("Level")
{
	// Creating a new grid.
	m_pGrid = new Grid(32, 18);
}

Level::~Level()
{
	// Delete the grid.
	delete m_pGrid;
}

void Level::Update(float fDeltaTime)
{
	// Updating the grid.
	m_pGrid->Update(fDeltaTime);

	// Updating base class.
	GameObject::Update(fDeltaTime);
}

void Level::Draw(aie::Renderer2D* pRenderer)
{
	// Draw the grid.
	m_pGrid->Draw(pRenderer);

	// Drawing base class.
	GameObject::Draw(pRenderer);
}

// Updating the solid nodes of the level via array.
void Level::UpdateSolidTiles(std::vector<Vector2> &prgSolidNodes)
{
	CollisionManager* pCM = CollisionManager::GetInstance();

	for (int i = 0; i < prgSolidNodes.size(); ++i)
	{
		Vector2 pNodePos = prgSolidNodes[i];
		Node* pNode = m_pGrid->GetNodeByPosition(pNodePos);

		if (pNode->m_pTile->GetBounds())
		{
			//pNode->m_pTile->UpdatePositionAndBounds(pNodePos);
			pNode->m_pTile->UpdateBounds(pNodePos);
			pCM->AddCollider(pNode->m_pTile);
		}
	}
}

// Returns the grid object.
Grid* Level::GetGrid()
{
	return m_pGrid;
}

// Set the players spawn.
void Level::SetPlayerSpawn(Vector2 v2Position)
{
	m_v2PlayerSpawn = v2Position;
}

// Get the players spawn.
Vector2 Level::GetPlayerSpawn()
{
	return m_v2PlayerSpawn;
}


