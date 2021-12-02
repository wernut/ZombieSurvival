#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class Entity : public GameObject
{
protected:
	Rectangle* m_prHitbox;
	TextureManager* m_pTextureManager;
	int m_nHealth, m_nMaxHealth;
	float m_fDamage;
	float m_fSpeed;
	float m_fCritcialHealth;
	Vector2 m_v2SpawnPosition;
	Vector2 m_v2StartPos, m_v2EndPos;
	std::vector<Vector2> m_rgPath;
	Vector2 m_v2Scale;
	bool m_bHasBeenHit;
	float m_fHitValue;
	bool m_bIsAlive;
	bool m_bHasBeenShot;
	bool m_bIsActive;

public:
	Entity(TextureManager::E_TEXTURES eTexture);
	Entity(TextureManager::E_TEXTURES eTexture, Vector2 v2Scale);
	virtual ~Entity();
	
	virtual void Update(float fDeltaTime);
	virtual void Draw(aie::Renderer2D* pRenderer);

	void TakeDamage(float nAmount);
	void SetStartPos(Vector2 v2StartPos);
	void SetEndPos(Vector2 v2EndPos);

	int GetHealth();
	void SetMaxHealth(int nHealth);
	int GetMaxHealth();
	void SetHasBeenShot(bool bHasBeenShot);
	bool GetHasBeenSot();
	bool IsAlive();
	virtual void SetAlive(bool bAlive);
	void SetHealth(int fHealth);
	Rectangle* GetHitbox();
	void SetSpawnPosition(Vector2 v2Position);
	Vector2 GetSpawnPosition();
	bool GetActive();
	void SetActive(bool bActive);
};

