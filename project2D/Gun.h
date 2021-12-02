#pragma once
#include "Weapon.h"
#include "DynamicArray.h"
#include "Ray.h"
#include "Level.h"

class Player;

class Gun : public Weapon
{
private:
	// Player and level.
	Player* m_pPlayer;
	Level* m_pLevel;

	// Gun properties.
	bool m_bHasShot;
	float m_fCooldown;
	float m_fCooldownMax;
	bool m_bReloading;
	int m_nHitCount;

	// Ray pool.
	DynamicArray<Ray*> m_prgUnactive;
	DynamicArray<Ray*> m_prgActive;
	DynamicArray<Vector2> m_prgNodeCheck;

public:
	Gun(Player* pPlayer, Level* pLevel);
	~Gun();

	void Shoot(float fDeltaTime);
	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);
};

