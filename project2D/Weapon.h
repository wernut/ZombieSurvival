#pragma once
#include "GameObject.h"
class Weapon : public GameObject
{
protected:
	int m_nDamage;
	int m_nAmmoCount;
	int m_nClipSize;
	int m_nMAX_AMMO;
	int m_nMAX_CLIP_SIZE;

public:
	Weapon(int fDamage, int nAmmo, int nClip, int MAX_AMMO, int MAX_CLIPSIZE);
	virtual ~Weapon();

	void Refill();
	virtual void Attack();

	void SetAmmo(int nAmmo);
	int GetAmmoCount();

	int GetClipSize();
};

