#include "CreatorState.h"
#include "Application.h"
#include "Grid.h"
#include "Input.h"
#include "StateMachine.h"
#include "TextureManager.h"

CreatorState::CreatorState(StateMachine* pStateMachine) : State(pStateMachine)
{
	// Setting the background colour.
	aie::Application* app = aie::Application::GetInstance();
	app->SetBackgroundColour(0.2f, 0.2f, 0.2f, 1.0f);

	// Create the texture picker.
	m_pTexturePicker = new TexturePicker();

	// Creating the tile saver.
	m_pTileSaver = new Loader(32, 18);

	// Create the level.
	m_pLevel = new Level();

	// Setting the selection box and checkpoint booleans to false.
	m_bIsSelecting = false;
	m_bCheckpointExists = false;
}

CreatorState::~CreatorState()
{
	// Delete the level.
	delete m_pLevel;

	// Delete the texture picker.
	delete m_pTexturePicker;
	m_pTexturePicker = nullptr;

	// Delete the tile saver.
	delete m_pTileSaver;
}

void CreatorState::OnEnter() 
{
	// Loading the level from the spawn file.
	Grid* pGrid = m_pLevel->GetGrid();
	Node*** aapNodeList = pGrid->GetNodeList();
	Vector2 v2PlayerSpawn = m_pLevel->GetPlayerSpawn();
	m_pTileSaver->Load(aapNodeList, v2PlayerSpawn, "./levels/spawn.LVL");
	m_pLevel->SetPlayerSpawn(v2PlayerSpawn);
	m_pLevel->UpdateSolidTiles(m_pTileSaver->GetSolidNodePos());
	pGrid->UpdateGrid();

	// Updating all solid nodes on the grid.
	for (int i = 0; i < m_pTileSaver->GetSolidNodePos().size(); ++i)
	{
		Vector2 v2Pos = m_pTileSaver->GetSolidNodeIndex(i);
		Node* pNode = m_pLevel->GetGrid()->GetNodeByPosition(v2Pos);

		m_pLevel->GetGrid()->CheckSolidNeighbours(pNode);
	}

	// Setting the show cursor boolean to true.
	aie::Application* app = aie::Application::GetInstance();
	app->SetShowCursor(true);
}

void CreatorState::Update(float fDeltaTime)
{
	// Getting some instances.
	CollisionManager* pCM = CollisionManager::GetInstance();
	TextureManager* pTM = TextureManager::GetInstance();
	aie::Input* pInput = aie::Input::GetInstance();

	// Update the level and the global transformation matrix.
	m_pLevel->Update(fDeltaTime);
	m_pLevel->UpdateGlobalTransform();

	// Updating the texture picker.
	m_pTexturePicker->Update(fDeltaTime);

	// Getting the mouse position.
	Vector2 v2MousePos;
	v2MousePos.x = (float)pInput->GetMouseX();
	v2MousePos.y = (float)pInput->GetMouseY();

	// Getting the level's grid.
	Grid* pGrid = m_pLevel->GetGrid();

	// Replacing a selected tile.
	if (pInput->IsMouseButtonDown(0) && !m_pTexturePicker->IsInside(v2MousePos))
	{
		Node* pNode = pGrid->GetNodeByPosition(v2MousePos);
		Tile* pTargetTile = pNode->m_pTile;
		Tile* pSelected = m_pTexturePicker->GetSelected();

		if (pSelected && pSelected->GetETexture() != pTargetTile->GetETexture())
		{
			// Making sure theres no more then 1 checkpoint.
			if (pSelected->GetETexture() == pTM->TILE_CHECKPOINT && m_bCheckpointExists)
			{
				Node* pCheckpoint = pGrid->GetNodeByPosition(m_pLevel->GetPlayerSpawn());
				int nTileID = (int)pCheckpoint->m_pTile->GetOverlayETexture();

				delete pCheckpoint->m_pTile;
				pCheckpoint->m_pTile = pTM->GetTileFromID(nTileID);
			}
			else
				m_bCheckpointExists = true;

			// Changing selected tile.
			this->ChangeTile(pSelected, pNode);
		}
		
		// Deleted the selected tile pointer.
		if (pSelected)
			delete pSelected;

		// Updating the grid.
		pGrid->UpdateGrid();
	}

	// Replace a selection of tiles.
	if (pInput->WasMouseButtonPressed(1) && !m_pTexturePicker->IsInside(v2MousePos))
	{
		// If we're replacing the spawn tile, then return out of this function.
		if (m_pTexturePicker->GetSelected()->GetETexture() == pTM->TILE_CHECKPOINT)
			return;

		SetSelectionPoint(0, pGrid->GetNodeByPosition(v2MousePos)->m_v2Position);
	}

	// Setting the end point of the selection box.
	if (pInput->IsMouseButtonDown(1) && !m_pTexturePicker->IsInside(v2MousePos))
	{
		if (m_pTexturePicker->GetSelected()->GetETexture() == pTM->TILE_CHECKPOINT)
			return;

		m_bIsSelecting = true;
		SetSelectionPoint(1, pGrid->GetNodeByPosition(v2MousePos)->m_v2Position);
	}

	// Replacing the selected tiles on the set dimensions
	if (pInput->WasMouseButtonReleased(1))
	{
		m_bIsSelecting = false;
		
		Tile* pSelected = m_pTexturePicker->GetSelected();
		if (pSelected)
		{
			ChangeTileArea(pSelected);
		}
	}

	// Entering the game via the enter key.
	if (pInput->WasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_pStateMachine->SetState(m_pStateMachine->ESTATE_GAME);
	}
}

// A function to determine the iteration type.
int CreatorState::DetermineIterationType(Vector2 v2Start, Vector2 v2End)
{
	if (v2Start.x <= v2End.x && v2Start.y <= v2End.y)
		return 0;
	if (v2Start.x <= v2End.x && v2Start.y >= v2End.y)
		return 1;  
	if (v2Start.x >= v2End.x && v2Start.y >= v2End.y)
		return 2;  
	if (v2Start.x >= v2End.x && v2Start.y <= v2End.y)
		return 3;

	return -1;
}

// Setting the location of the start (0) or end (1) position for the selection box.
void CreatorState::SetSelectionPoint(int nIndex, Vector2 v2Position)
{
	m_aSelectionPoints[nIndex] = v2Position;
}

// Changing an area of tiles.
void CreatorState::ChangeTileArea(Tile* &pSelected)
{
	Vector2 v2Start = m_aSelectionPoints[0];
	Vector2 v2End = m_aSelectionPoints[1];
	int startX = (int)(v2Start.x - (SQUARE_SIZE / 2));
	int startY = (int)(v2Start.y - (SQUARE_SIZE / 2));
	int endX = (int)(v2End.x + (SQUARE_SIZE / 2));
	int endY = (int)(v2End.y + (SQUARE_SIZE / 2));

	// Currently using a different for loop to iterate through the correct axis.
	// Need to find an easier and cheaper way of doing this.
	switch (DetermineIterationType(v2Start, v2End))
	{
		// Top right selection.
	case 0:
		for (int x = startX; x < endX; ++x)
			for (int y = startY; y < endY; ++y)
				ChangeTileModulas(pSelected, x, y);
		break;

	case 1:
		// Bottom right selection.
		for (int x = startX; x < endX; ++x)
			for (int y = endY; y < startY; ++y)
				ChangeTileModulas(pSelected, x, y);
		break;

	case 2:
		// Bottom left selection.
		for (int x = endX; x < startX; ++x)
			for (int y = endY; y < startY; ++y)
				ChangeTileModulas(pSelected, x, y);
		break;

	case 3:
		// Top left selection.
		for (int x = endX; x < startX; ++x)
			for (int y = startY; y < endY; ++y)
				ChangeTileModulas(pSelected, x, y);
		break;

	}

	if(pSelected)
		delete pSelected;
}

// Change the tile of a node to a selected tile. 
void CreatorState::ChangeTile(Tile* pSelected, Node* pNode)
{
	CollisionManager* pCM = CollisionManager::GetInstance();
	TextureManager* pTM = TextureManager::GetInstance();
	Tile* pTargetTile = pNode->m_pTile;


	// If the tile we're trying to replace is solid, the remove that collider.
	if (pTargetTile->IsSolid())
	{
		pCM->RemoveCollider(pTargetTile);
	}

	// If the tile we've selected isn't transparent, then we simply replace the tile.
	if (!pSelected->IsTransparent())
	{
		// Replace tile.
		delete pTargetTile;
		pNode->m_pTile = pSelected;
	}
	// If the tile is transparent, then we keep the target texture underneath and replace the tile.
	else
	{
		// Place tile without deleting underlying texture.
		pNode->m_pTile = pSelected;
		pNode->m_pTile->SetOverlayTexture(pTargetTile->GetETexture());
		delete pTargetTile;
	}
	
	// If the selected tile is solid, then we need up update the bounds and add the collider to the array.
	if (pNode->m_pTile->IsSolid())
	{
		pNode->m_pTile->UpdateBounds(pNode->m_v2Position);
		pCM->AddCollider(pNode->m_pTile);
	}

	// If the selected tile is the checkpoint tile, then set the player's position to that tile.
	if (pSelected->GetETexture() == pTM->TILE_CHECKPOINT)
	{
		m_pLevel->SetPlayerSpawn(pNode->m_v2Position);
	}

	// If the target node is the checkpoint tile, then we want to set the check point exists bool to false.
	if (pTargetTile->GetETexture() == pTM->TILE_CHECKPOINT)
	{
		m_bCheckpointExists = false;
	}

	// Updating the grid.
	m_pLevel->GetGrid()->CheckSolidNeighbours(pNode);
}

void CreatorState::ChangeTileModulas(Tile* pSelected, int x, int y)
{
	if ((x % (int)SQUARE_SIZE) == 0 && (y % (int)SQUARE_SIZE) == 0)
	{
		Node* pNode = m_pLevel->GetGrid()->GetNodeByPosition(Vector2((float)x, (float)y));
		this->ChangeTile(pSelected, pNode);
	}
}

void CreatorState::Draw(aie::Renderer2D* pRenderer)
{
	aie::Input* pInput = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = (float)pInput->GetMouseX();
	v2MousePos.y = (float)pInput->GetMouseY();

	Node* pNode = m_pLevel->GetGrid()->GetNodeByPosition(v2MousePos);

	// Draw all the levels children.
	m_pLevel->Draw(pRenderer);

	// Drawing the highlight box.
	pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f, 0.3f);
	if (m_pLevel->GetGrid()->IsInside(v2MousePos, pNode->m_v2Position, SQUARE_SIZE))
	{
		pRenderer->DrawBox(pNode->m_v2Position.x, pNode->m_v2Position.y, SQUARE_SIZE, SQUARE_SIZE);
	}
	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	// Draw the selection box.
	if (m_bIsSelecting)
	{
		// Line.
		pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f, 1.0f);
		pRenderer->DrawLine(m_aSelectionPoints[0].x - (SQUARE_SIZE / 2), m_aSelectionPoints[0].y - (SQUARE_SIZE / 2), m_aSelectionPoints[1].x + (SQUARE_SIZE / 2), m_aSelectionPoints[1].y + (SQUARE_SIZE / 2), 2.0f);
		pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f, 0.2f);

		// Box.
		float fWidth = m_aSelectionPoints[1].x - m_aSelectionPoints[0].x;
		float fHeight = m_aSelectionPoints[1].y - m_aSelectionPoints[0].y;
		pRenderer->DrawBox(m_aSelectionPoints[0].x + (fWidth / 2), m_aSelectionPoints[0].y + (fHeight / 2), fWidth + SQUARE_SIZE, fHeight + SQUARE_SIZE);
		pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Drawing the texture picker.
	m_pTexturePicker->Draw(pRenderer);
}

void CreatorState::OnExit() 
{
	// Temp console commands.
	char szInputBuffer[64];
	system("cls");
	std::cout << "Please enter a level name to save to: " << std::endl;
	std::cout << "Note: Will overwrite anything with the same name, so choose carefully." << std::endl;
	std::cin >> szInputBuffer;
	strcat_s(szInputBuffer, ".LVL");
	char szFinal[64];
	strcpy_s(szFinal, "./levels/");
	strcat_s(szFinal, szInputBuffer);

	// Saving the level.
	Node*** aapNodeList = m_pLevel->GetGrid()->GetNodeList();
	m_pTileSaver->Save(aapNodeList, m_pLevel->GetPlayerSpawn(), szFinal);
}
