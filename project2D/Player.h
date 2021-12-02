#pragma once
#include "Entity.h"
#include "Inventory.h"
#include "Weapon.h"

enum EPLAYERSTATE
{
	EPLAYERSTATE_IDLE,
	EPLAYERSTATE_MOVE,
	EPLAYERSTATE_SHOOT,
	EPLAYERSTATE_RELOAD,
	EPLAYERSTATE_COUNT,
};

class Player : public Entity
{
private:
	EPLAYERSTATE m_eCurrentState;
	Inventory* pInv;
	bool m_bShooting;
	Weapon* m_pCurrentWeapon;
	int m_nScore;

	// State animations.
	void DrawIdle(aie::Renderer2D* &pRenderer, int &frame, float &size);
	void DrawMove(aie::Renderer2D* &pRenderer, int &frame, float &size);
	void DrawShoot(aie::Renderer2D* &pRenderer, int &frame, float &size);
	void DrawReload(aie::Renderer2D* &pRenderer, int &frame, float &size);

public:
	Player();
	~Player();

	void Draw(aie::Renderer2D* pRenderer);
	void Update(float fDeltaTime);
	void OnCollision(GameObject* pGameObject, int nSide);
	void DrawState(aie::Renderer2D* &pRenderer, int &frame, float &size);
	void SwitchState(EPLAYERSTATE eNewState);
	void SetFire(bool bFire);
	void SetCurrentWeapon(Weapon* pWeapon);
	void SetScore(int nScore);
	int GetScore();
	Weapon* GetCurrentWeapon();
	Inventory* GetInventory();
};

