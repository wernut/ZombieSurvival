#include "PathHeap.h"
#include "Node.h"
#include <algorithm>

PathHeap::PathHeap(){}

PathHeap::~PathHeap(){}

void PathHeap::Push(Node* pNode)
{
	// Adding the node to the heap.
	m_rgHeap.push_back(pNode);

	int nCurrent = (int) m_rgHeap.size() - 1;
	int nParent = GetParent(nCurrent);

	// While the current gscore is less then the parents, then do the following.
	while (m_rgHeap[nCurrent]->m_nFScore < m_rgHeap[nParent]->m_nFScore)
	{
		// Swap the current with the parent node.
		Node* pTempNode = m_rgHeap[nCurrent];
		m_rgHeap[nCurrent] = m_rgHeap[nParent];
		m_rgHeap[nParent] = pTempNode;

		// Setting the current node to be the parent and getting the new parent.
		nCurrent = nParent;
		nParent = GetParent(nCurrent);
	}

}

Node* PathHeap::Pop()
{
	Node* pNode = m_rgHeap[0];

	int nLast = (int) m_rgHeap.size() - 1;
	int nCurrent = 0;

	m_rgHeap[nCurrent] = m_rgHeap[nLast];
	m_rgHeap.pop_back();

	int nChild1Index = GetChild(nCurrent, 1);
	int nChild2Index = GetChild(nCurrent, 2);

	int nCheapestIndex = nChild1Index;
	if (nCheapestIndex >= m_rgHeap.size())
		return pNode;

	if(nChild2Index < m_rgHeap.size() && m_rgHeap[nChild2Index]->m_nFScore < m_rgHeap[nCheapestIndex]->m_nFScore)
		nCheapestIndex = nChild2Index;

	while (m_rgHeap[nCheapestIndex]->m_nFScore < m_rgHeap[nCurrent]->m_nFScore)
	{
		Node* pSwap = m_rgHeap[nCheapestIndex];
		m_rgHeap[nCheapestIndex] = m_rgHeap[nCurrent];
		m_rgHeap[nCurrent] = pSwap;

		nCurrent = nCheapestIndex;
		nChild1Index = GetChild(nCurrent, 1);
		nChild2Index = GetChild(nCurrent, 2);

		nCheapestIndex = nChild1Index;
		if (nCheapestIndex >= m_rgHeap.size())
			return pNode;

		if (nChild2Index < m_rgHeap.size() && m_rgHeap[nChild2Index]->m_nFScore < m_rgHeap[nCheapestIndex]->m_nFScore)
			nCheapestIndex = nChild2Index;
	}

	return pNode;
}

bool PathHeap::Find(Node* pNode)
{
	return std::find(m_rgHeap.begin(), m_rgHeap.end(), pNode) != m_rgHeap.end();
}

void PathHeap::Clear()
{
	m_rgHeap.clear();
}

int PathHeap::GetParent(int nIndex)
{
	return (nIndex - 1) / 2;
}

int PathHeap::GetChild(int nIndex, int nChild)
{
	return (2 * nIndex) + nChild;
}

int PathHeap::GetCount()
{
	return (int) m_rgHeap.size();
}