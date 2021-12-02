#pragma once
#include "Node.h"
#include "Tile.h"
#include "DynamicArray.h"
#include "CollisionManager.h"
#include <vector>
#include <fstream>
#include <iostream>

class Loader
{
private:
	std::fstream m_pFile;
	int m_nWidth, m_nHeight;
	std::vector<Vector2> m_prgSolidNodes;
	std::vector<Vector2> m_prgZombieSpawnPos;
	Vector2 m_v2Previous;

public:
	Loader(int nWidth, int nHeight)
	{
		this->m_nWidth = nWidth;
		this->m_nHeight = nHeight;
	}
	~Loader() {}

	void Load(Node*** &aapNodeList, Vector2 &v2CheckpointLocation, char* szFileLocation)
	{
		TextureManager* pTM = TextureManager::GetInstance();
		CollisionManager* pCM = CollisionManager::GetInstance();

		// Opening the saved file and reading in binary.
		m_pFile.open(szFileLocation, std::ios_base::in | std::ios_base::binary);
		if (m_pFile.is_open())
		{
			// Reading in the checkpoint location.
			m_pFile.read((char*)&v2CheckpointLocation.x, sizeof(float));
			m_pFile.read((char*)&v2CheckpointLocation.y, sizeof(float));

			// Clearing the solid node and tombstone arrays.
			if (m_prgSolidNodes.size() > 0)
				m_prgSolidNodes.clear();

			if (m_prgZombieSpawnPos.size() > 0)
				m_prgZombieSpawnPos.clear();

			// While it's not the end of the file, read in the data.
			for (int x = 0; x < m_nWidth; ++x)
			{
				for (int y = 0; y < m_nHeight; ++y)
				{
					// Read in the texture ID.
					int nTexture = aapNodeList[x][y]->m_pTile->GetETexture();
					m_pFile.read((char*)&nTexture, sizeof(int));

					// Read in overlay texture ID.
					int nOverlayTexture = aapNodeList[x][y]->m_pTile->GetOverlayETexture();
					m_pFile.read((char*)&nOverlayTexture, sizeof(int));

					// Set the tile based on ID.
					delete aapNodeList[x][y]->m_pTile;
					aapNodeList[x][y]->m_pTile = pTM->GetTileFromID(nTexture);

					// Set the overlay tile.
					if (nOverlayTexture > 0)
						aapNodeList[x][y]->m_pTile->SetOverlayTexture(nOverlayTexture);

					// Adding solid node positions to array.
					if (aapNodeList[x][y]->m_pTile->IsSolid())
					{
						pCM->RemoveCollider(aapNodeList[x][y]->m_pTile);
						m_prgSolidNodes.push_back(Vector2(aapNodeList[x][y]->m_v2Position));
					}

					// Adding tombstone to the array.
					if (aapNodeList[x][y]->m_pTile->GetETexture() == pTM->TILE_PENTAGRAM_ANIMATION)
					{
						Vector2 v2SpawnLocation = aapNodeList[x][y]->m_v2Position;
						if (v2SpawnLocation != m_v2Previous)
						{
							m_prgZombieSpawnPos.push_back(v2SpawnLocation);
							m_v2Previous = v2SpawnLocation;
						}
					}
				}
			}
			// Closing the file.
			m_pFile.close();
		}
	}

	void Save(Node*** aapNodeList, Vector2 v2CheckpointLocation, const char* szFileLocation)
	{
 		// Opening the file.
		m_pFile.open(szFileLocation, std::ios_base::out | std::ios_base::binary);

		std::cout << "Saving to: " << szFileLocation << std::endl;

		if (m_pFile.is_open())
		{
			// Saving the level's checkpoint location.
			m_pFile.write((char*)&v2CheckpointLocation.x, sizeof(float));
			m_pFile.write((char*)&v2CheckpointLocation.y, sizeof(float));

			// Saving the grid information.
			for (int x = 0; x < m_nWidth; ++x)
			{
				for (int y = 0; y < m_nHeight; ++y)
				{
					int nTexture = aapNodeList[x][y]->m_pTile->GetETexture();
					m_pFile.write((char*)&nTexture, sizeof(int));

					int nOverlayTexture = aapNodeList[x][y]->m_pTile->GetOverlayETexture();
					m_pFile.write((char*)&nOverlayTexture, sizeof(int));
				}
			}

			m_pFile.flush();
			m_pFile.close();
		}
	}

	std::vector<Vector2> GetSolidNodePos()
	{
		return m_prgSolidNodes;
	}

	std::vector<Vector2> GetZombieSpawnPos()
	{
		return m_prgZombieSpawnPos;
	}

	Vector2 GetSolidNodeIndex(int nIndex)
	{
		return m_prgSolidNodes[nIndex];
	}

	Vector2 GetZombieSpawnIndex(int nIndex)
	{
		return m_prgZombieSpawnPos[nIndex];
	}
};


