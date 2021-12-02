#pragma once
#include "GameObject.h"
#include "DynamicArray.h"
#include "Entity.h"

class CollisionManager
{
private:
	static CollisionManager* m_pInstance;
	DynamicArray<GameObject*> m_prgBounds;
	DynamicArray<Entity*> m_prgHitbox;
public:
	CollisionManager();
	~CollisionManager();

	void AddCollider(GameObject* pGameObject);
	void RemoveCollider(GameObject* pGameObject);
	void AddHitbox(Entity* pEntity);
	void RemoveHitbox(Entity* pEntity);
	void Update(float fDeltaTime);
	int GetColliderArraySize();
	int GetHitboxArraySize();
	Entity* GetHitboxArrayIndex(int nIndex);
	DynamicArray<Entity*> GetHitboxArray();

	static void Create()
	{
		if(!m_pInstance)
			m_pInstance = new CollisionManager();
	}

	static void Delete()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	static CollisionManager* GetInstance() { return m_pInstance; }
};

