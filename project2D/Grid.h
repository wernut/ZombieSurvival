#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include "PathHeap.h"
#include <vector>

struct Node;

class Grid
{
private:
	int m_nWidth, m_nHeight;
	Node*** m_aapNodeList;
	PathHeap m_prgOpenList;
	bool* m_bClosedList;
public:
	Grid(int nWidth, int nHeight);
	~Grid();

	bool IsInside(Vector2 v2MousePos, Vector2 v2Position, float v2Scale);
	void Update(float fDeltaTime);
	void UpdateGrid();
	void Draw(aie::Renderer2D* pRenderer);
	void CheckSolidNeighbours(Node* &pNode);
	Node* GetRandomNode();
	Node*** GetNodeList();
	void SetNodeList(Node*** appNodeList);
	Node* GetNodeByPosition(Vector2 v2Position);
	bool FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& rgPath);
	int CalculateHeuristic(Node* pNode, Node* pEnd);
};

