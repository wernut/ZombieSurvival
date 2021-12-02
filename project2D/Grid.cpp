#include "Grid.h"
#include "Node.h"
#include "Vector2.h"
#include "GrassTile.h"
#include "DirtTile.h"
#include "Application.h"
#include "Input.h"
#include "CollisionManager.h"
#include <iostream>
#include <cmath>
#include <vector>

#define SQUARE_SIZE 40.0f
#define GRID_POSX 20
#define GRID_POSY 20
#define ADJACENT_COST 10
#define DIAGONAL_COST 14

Grid::Grid(int nWidth, int nHeight)
{
	// Set the size of grid.
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	// Allocate 2D array of pointers that will be used to store nodes.
	m_aapNodeList = new Node**[m_nWidth];
	for (int i = 0; i < m_nWidth; ++i)
	{
		m_aapNodeList[i] = new Node*[m_nHeight];
	}

	// Allocate the nodes.
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			Vector2 v2Pos;
			v2Pos.x = x * SQUARE_SIZE + GRID_POSX;
			v2Pos.y = y * SQUARE_SIZE + GRID_POSY;
			m_aapNodeList[x][y] = new Node(v2Pos, x, y, new GrassTile(v2Pos, x, y));
		}
	}

	// Connect nodes to their neighbours.
	/*
			| 7 | 2 | 6 |
			| 1 | C | 3 |
			| 4 | 0 | 5 |
	*/
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			if (y > 0)
				m_aapNodeList[x][y]->m_apNeighbours[0] = m_aapNodeList[x][y - 1];

			if (x > 0)
				m_aapNodeList[x][y]->m_apNeighbours[1] = m_aapNodeList[x - 1][y];

			if (y < m_nHeight - 1)
				m_aapNodeList[x][y]->m_apNeighbours[2] = m_aapNodeList[x][y + 1];

			if (x < m_nWidth - 1)
				m_aapNodeList[x][y]->m_apNeighbours[3] = m_aapNodeList[x + 1][y];

			if (y > 0 && x > 0)
				m_aapNodeList[x][y]->m_apNeighbours[4] = m_aapNodeList[x][y - 1];

			if (y > 0 && x < m_nWidth - 1)
				m_aapNodeList[x][y]->m_apNeighbours[5] = m_aapNodeList[x + 1][y - 1];

			if (y < m_nHeight - 1 && x < m_nWidth - 1)
				m_aapNodeList[x][y]->m_apNeighbours[6] = m_aapNodeList[x + 1][y + 1];

			if (y < m_nHeight - 1 && x > 0)
				m_aapNodeList[x][y]->m_apNeighbours[7] = m_aapNodeList[x - 1][y + 1];

			// Setting the costs.
			m_aapNodeList[x][y]->m_anCost[0] = ADJACENT_COST;
			m_aapNodeList[x][y]->m_anCost[1] = ADJACENT_COST;
			m_aapNodeList[x][y]->m_anCost[2] = ADJACENT_COST;
			m_aapNodeList[x][y]->m_anCost[3] = ADJACENT_COST;
			// ----------------------------------------------
			m_aapNodeList[x][y]->m_anCost[4] = DIAGONAL_COST;
			m_aapNodeList[x][y]->m_anCost[5] = DIAGONAL_COST;
			m_aapNodeList[x][y]->m_anCost[6] = DIAGONAL_COST;
			m_aapNodeList[x][y]->m_anCost[7] = DIAGONAL_COST;
		}
	}

	// Create the closed list.
	m_bClosedList = new bool[m_nWidth * m_nHeight];
}

Grid::~Grid()
{
	// Deleting all the allocated nodes.
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			delete m_aapNodeList[x][y];
			m_aapNodeList[x][y] = nullptr;
		}
	}

	for (int i = 0; i < m_nWidth; ++i)
	{
		delete[] m_aapNodeList[i];
		m_aapNodeList[i] = nullptr;
	}

	delete[] m_aapNodeList;
	m_aapNodeList = nullptr;

	delete[] m_bClosedList;
	m_bClosedList = nullptr;
}

void Grid::UpdateGrid()
{
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			Node* pNode = m_aapNodeList[x][y];
			if (pNode->m_pTile)
			{
				bool bBlocked = pNode->m_pTile->IsSolid();
				pNode->m_bBlocked = bBlocked;
				if (pNode->m_pTile->GetBounds())
				{
					pNode->m_pTile->UpdateBounds(pNode->m_v2Position);
				}
			}
		}
	}
}

void Grid::Update(float fDeltaTime){}

void Grid::Draw(aie::Renderer2D* pRenderer)
{
	//// Get mouse position.
	//aie::Input* pInput = aie::Input::GetInstance();
	//Vector2 v2MousePos;
	//v2MousePos.x = (float)pInput->GetMouseX();
	//v2MousePos.y = (float)pInput->GetMouseY();

	// Drawing the grid.
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			// Drawing the tiles.
			Vector2 v2Pos = m_aapNodeList[x][y]->m_v2Position;
			m_aapNodeList[x][y]->m_pTile->Draw(pRenderer, v2Pos, Vector2(SQUARE_SIZE, SQUARE_SIZE));
		}
	}
}

Node* Grid::GetNodeByPosition(Vector2 v2Position)
{
	Node* pNode = nullptr;

	int x = (int) ((v2Position.x - GRID_POSX + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);
	int y = (int) ((v2Position.y - GRID_POSY + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);

	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	if (x > m_nWidth - 1)
		x = m_nWidth - 1;

	if (y > m_nHeight - 1)
		y = m_nHeight - 1;

	pNode = m_aapNodeList[x][y];

	return pNode;
}

bool Grid::IsInside(Vector2 v2MousePos, Vector2 v2Position, float v2Scale)
{
	return v2MousePos.x > v2Position.x - (v2Scale / 2) &&
		v2MousePos.x < v2Position.x + (v2Scale / 2) &&
		v2MousePos.y > v2Position.y - (v2Scale / 2) &&
		v2MousePos.y < v2Position.y + (v2Scale / 2);
}

int Grid::CalculateHeuristic(Node* pNode, Node* pEnd)
{
	int nDistX = abs(pNode->m_nIndexX - pEnd->m_nIndexX);
	int nDistY = abs(pNode->m_nIndexY - pEnd->m_nIndexY);

	if (nDistX > nDistY)
		return (DIAGONAL_COST * nDistY) + ADJACENT_COST * (nDistX - nDistY);
	else
		return (DIAGONAL_COST * nDistX) + ADJACENT_COST * (nDistY - nDistX);
}

bool Grid::FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& rgPath)
{
	// Find start and end nodes.
	Node* pStartNode = GetNodeByPosition(v2Start);
	Node* pEndNode = GetNodeByPosition(v2End);
	rgPath.clear();

	// Checking for nullptr.
	if (!pStartNode || !pEndNode)
		return false;

	// Checking if the start node is the end node.
	if (pStartNode == pEndNode)
		return false;

	// Checking if the start and end are blocked.
	if (pStartNode->m_bBlocked || pEndNode->m_bBlocked)
		return false;

	// Initialization.
	m_prgOpenList.Clear();
	memset(m_bClosedList, 0, sizeof(bool) * m_nWidth * m_nHeight);
	bool bFoundPath = false;

	// Setting the start nodes properties and adding it to the open list.
	pStartNode->m_pPrev = nullptr;
	pStartNode->m_nGScore = 0;
	pStartNode->m_nHScore = CalculateHeuristic(pStartNode, pEndNode);
	pStartNode->m_nFScore = pStartNode->m_nGScore + pStartNode->m_nHScore;
	m_prgOpenList.Push(pStartNode);

	// The algorithm!
	while (m_prgOpenList.GetCount() > 0)
	{
		//SortOpenList();

		// Remove from open list.
		Node* pCurrent = m_prgOpenList.Pop();

		// Add to closed list.
		int nIndex = pCurrent->m_nIndexY * m_nWidth + pCurrent->m_nIndexX;
		m_bClosedList[nIndex] = true;

		// Checking for completed path.
		if (pCurrent == pEndNode)
		{
			bFoundPath = true;
			break;
		}

		for (int i = 0; i < NEIGHBOUR_COUNT; ++i)
		{
			Node* pNeighbour = pCurrent->m_apNeighbours[i];

			// Skip if pNeighbour is null.
			if (!pNeighbour)
				continue;

			// Skip if pNeighbour is blocked.
			if (pNeighbour->m_bBlocked)
				continue;

			// Skip if pNeighbour is in the closed list.
			int nNeighbourIndex = pNeighbour->m_nIndexY * m_nWidth + pNeighbour->m_nIndexX;
			if (m_bClosedList[nNeighbourIndex])
				continue;

			// Check if in the open list.
			if (!m_prgOpenList.Find(pNeighbour))
			{
				// Not in the open list.
				pNeighbour->m_pPrev = pCurrent;
				pNeighbour->m_nGScore = pCurrent->m_nGScore + pCurrent->m_anCost[i];
				pNeighbour->m_nHScore = CalculateHeuristic(pNeighbour, pEndNode);
				pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;
				m_prgOpenList.Push(pNeighbour);
			}
			else
			{
				//Is in open list, check if this is a better path
				int nCost = pCurrent->m_nFScore + pCurrent->m_anCost[i];
				if (nCost < pNeighbour->m_nFScore)
				{
					pNeighbour->m_nGScore = pCurrent->m_nGScore + pCurrent->m_anCost[i]; 
					pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;
					pNeighbour->m_pPrev = pCurrent;
				}
			}
		}
	}

	if (bFoundPath)
	{
		Node* pCurrent = pEndNode;
		while (pCurrent)
		{
			rgPath.insert(rgPath.begin(), pCurrent->m_v2Position);
			pCurrent = pCurrent->m_pPrev;
		}
		return true;
	}
	return false;
}

Node*** Grid::GetNodeList()
{
	return m_aapNodeList;
}

void Grid::SetNodeList(Node*** aapNodeList)
{
	memcpy_s(m_aapNodeList, sizeof(Node) + (m_nWidth * m_nHeight), aapNodeList, sizeof(Node) + (m_nWidth * m_nHeight));
	UpdateGrid();
}

void Grid::CheckSolidNeighbours(Node* &pNode)
{
	Tile* pTile = pNode->m_pTile;
	bool bSolid = false;
	for (int i = 0; i < 4; ++i)
	{
		if (pNode->m_apNeighbours[i])
		{
			Tile* pNeighbour = pNode->m_apNeighbours[i]->m_pTile;

			if (pNeighbour->IsSolid())
			{
				
				if (pTile->IsSolid())
				{
					bSolid = false;
					pTile->GetBounds()->SetActiveLine(i, false);
				}
				else
					bSolid = true;
				

				if (i <= 1)
					pNeighbour->GetBounds()->SetActiveLine(i + 2, bSolid);
				else if (i >= 2)
					pNeighbour->GetBounds()->SetActiveLine(i - 2, bSolid);
			}
		}
	}
}

Node* Grid::GetRandomNode()
{
	TextureManager* pTM = TextureManager::GetInstance();
	int randX = 0, randY = 0;
	Node* pNode = nullptr;

	while (true)
	{
		// Getting the random coords.
		randX = rand() % m_nWidth * SQUARE_SIZE + GRID_POSX;
		randY = rand() % m_nHeight * SQUARE_SIZE + GRID_POSX;

		// Getting the node from those coords.
		pNode = GetNodeByPosition(Vector2(randX, randY));

		// Recursivly finding another node if the random node is blocked.
		if (pNode->m_pTile->GetETexture() == pTM->TILE_GRASS)
			return pNode;
	}

	return nullptr;
}