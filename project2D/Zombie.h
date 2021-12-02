#pragma once
#include "Entity.h"
#include "Player.h"
#include "Grid.h"

#define DEBUG_COUNT 3

class Zombie : public Entity
{
private:
	enum EAISTATE
	{
		EAISTATE_SPAWN,
		EAISTATE_SEARCH,
		EAISTATE_CHASE,
		EAISTATE_ATTACK,
		EAISTATE_FLEE,
		EAISTATE_DEATH,
		EAISTATE_COUNT,
	};

	Grid* m_pGrid;
	Player* m_pPlayer;
	EAISTATE m_eCurrentState;

	bool m_bRecalculate;
	bool m_bHasAttacked;
	bool m_bAnimation;
	bool m_bIsSearching;
	bool m_bHasSeenPlayer;
	bool m_baDebugOptions[DEBUG_COUNT];

	int m_nNodePos;
	int m_nFrame;
	int m_nDebugOptions;

	float m_fAttackTimer;
	float m_fTimer, m_fMaxTimer, m_fTimerSpeed;
	float m_fRangeOfSight, m_fRangeOfAttack, m_fRangeOfFlee;
	float m_fSearchingSpeed;
	float m_fShotTimer, m_fMaxShotTimer;
	float m_fRegenTimer, m_fRegenSpeed;

	Vector2 m_v2LastKnownLocation;


	// AI States.
	void UpdateState(float fDeltaTime);
	void SpawnIn(float fDeltaTime);
	void Search(float fDeltaTime);
	void Chase(float fDeltaTime);
	void Death(float fDeltaTime);
	void Attack(float fDeltaTime); 
	void Flee(float fDeltaTime);

	// AI functions.
	bool IsInRange(float fRange, Vector2 v2TargetPos);
	void RotateAndSeek(Vector2 v2Target, float fDeltaTime);
	void ChangeTexture(TextureManager::E_TEXTURES eTexture);
	void MoveAlongPath(float fDeltaTime);

	// Draw functions.
	void DrawAnimation(aie::Renderer2D* &pRenderer, float &fTime, float animSpeed, int frameCount);
	void DrawDebugInformation(aie::Renderer2D* pRenderer);

public:
	Zombie(Grid* pGrid, Player* pPlayer);
	~Zombie();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
	void OnCollision(GameObject* pGameObject, int nSide);
	void SetAlive(bool bAlive);
};

