#include "Node.h"
#include "TextureManager.h"

Node::Node(Vector2 v2Pos, int nIndexX, int nIndexY, Tile* pTile)
{
	m_pPrev = nullptr;
	m_v2Position = v2Pos;
	m_nGScore = 0;
	m_nFScore = 0;
	m_nHScore = 0;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;
	m_pTile = pTile;
	m_bBlocked = m_pTile->IsSolid();
	for (int i = 0; i < NEIGHBOUR_COUNT; ++i)
	{
		m_apNeighbours[i] = nullptr;
		m_anCost[i] = 0;
	}
}

Node::~Node()
{
	if (m_pTile)
	{
		delete m_pTile;
		m_pTile = nullptr;
	}
}