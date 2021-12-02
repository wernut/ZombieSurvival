#include "Weapon.h"

Weapon::Weapon(int fDamage, int nAmmo, int nClip, int MAX_AMMO, int MAX_CLIPSIZE) : GameObject("Weapon")
{
	m_nDamage = fDamage;
	m_nAmmoCount = nAmmo;
	m_nClipSize = nClip;
	m_nMAX_AMMO = MAX_AMMO;
	m_nMAX_CLIP_SIZE = MAX_CLIPSIZE;
}

Weapon::~Weapon(){}

void Weapon::Attack(){}

void Weapon::Refill()
{
	m_nAmmoCount = m_nMAX_AMMO;
	m_nClipSize = m_nMAX_CLIP_SIZE;
}

void Weapon::SetAmmo(int nAmmo)
{
	m_nAmmoCount = nAmmo;
}

int Weapon::GetAmmoCount()
{
	return m_nAmmoCount;
}

int Weapon::GetClipSize()
{
	return m_nClipSize;
}