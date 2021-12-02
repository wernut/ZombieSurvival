#pragma once
#include <vector>

struct Node;

class PathHeap
{
private:
	int GetParent(int nIndex);
	int GetChild(int nIndex, int nChild);
	std::vector<Node*> m_rgHeap;
public:
	PathHeap();
	~PathHeap();
	int GetCount();
	void Push(Node* pNode);
	Node* Pop();
	void Clear();
	bool Find(Node* pNode);
};