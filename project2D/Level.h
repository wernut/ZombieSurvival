#pragma once
#include "GameObject.h"
#include "DynamicArray.h"
#include "Font.h"
#include "TileSaver.h"
#include <vector>

class Grid;
struct Node;

class Level : public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	void UpdateSolidTiles(std::vector<Vector2> &prgSolidNodes);
	Grid* GetGrid();
	void SetPlayerSpawn(Vector2 v2Position);
	Vector2 GetPlayerSpawn();

private:
	Grid* m_pGrid;
	bool m_bShowTextureGrid;
	Loader* m_pTileSaver;
	Vector2 m_v2PlayerSpawn;
};

