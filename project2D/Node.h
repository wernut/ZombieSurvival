#pragma once
#include "Vector2.h"
#include "Renderer2D.h"
#include "Tile.h"
#include "TextureManager.h"

#define NEIGHBOUR_COUNT 8

struct Node
{
public:
	Node(Vector2 v2Pos, int nIndexX, int nIndexY, Tile* pTile);
	~Node();
	Vector2 m_v2Position;
	Node* m_apNeighbours[NEIGHBOUR_COUNT];
	Node* m_pPrev;
	Tile* m_pTile;
	int m_nGScore, m_nFScore, m_nHScore;
	int m_nIndexX, m_nIndexY;
	int m_anCost[NEIGHBOUR_COUNT];
	bool m_bBlocked;
};

