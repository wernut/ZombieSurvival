#include <iostream>
#include "CollisionManager.h"
#include "StoneTile.h"
#include "WellTile.h"
#include "TextureManager.h"

CollisionManager* CollisionManager::m_pInstance = nullptr;

CollisionManager::CollisionManager(){}

CollisionManager::~CollisionManager(){}

void CollisionManager::AddCollider(GameObject* pGameObject)
{
	// Adding an object to the collider array.
	m_prgBounds.PushBack(pGameObject);
}

void CollisionManager::RemoveCollider(GameObject* pGameObject)
{
	// Removing an object to the collider array.
	m_prgBounds.Remove(pGameObject);
}

void CollisionManager::AddHitbox(Entity* pEntity)
{
	// Adding an object to the collider array.
	m_prgHitbox.PushBack(pEntity);
}

void CollisionManager::RemoveHitbox(Entity* pEntity)
{
	// Removing an object to the collider array.
	m_prgHitbox.Remove(pEntity);
}


void CollisionManager::Update(float fDeltaTime)
{
	// Getting the amount of objects in the collider array.
	int nSize = m_prgBounds.GetSize();

	// Iterating through the array and checking each object against one another to determine if they are colliding.
	for (int i = 0; i < nSize; ++i)
	{
		for (int j = 0; j < nSize; ++j)
		{
			// Making sure i doesn't equal j, so we don't check the object against itself.
			if (i == j)
				continue;

			// Defining 2 new GameObjects to hold the data of the object's we are checking.
			GameObject* pGameObject = m_prgBounds[i];
			GameObject* _pGameObject = m_prgBounds[j];

			// Objects with the same tag will never collide with each other.
			if (strcmp(pGameObject->GetTag(), _pGameObject->GetTag()) == 0)
				continue;

			// Checking if the bounds requires sides to snap to or if it will just intersect.
			if (pGameObject->RequiresSide() && _pGameObject->GetBounds())
			{
				// Getting what side the object is colliding with.
				int nSide = pGameObject->GetBounds()->LineInterects(_pGameObject->GetBounds());

				if (nSide != -1)
					pGameObject->OnCollision(_pGameObject, nSide);
			}
			// Normal intersection otherwise.
			else if (pGameObject->GetBounds()->Intersects(_pGameObject->GetBounds()))
			{
				pGameObject->OnCollision(_pGameObject);
			}
		}
	}
}

int CollisionManager::GetColliderArraySize() 
{
	return (int) m_prgBounds.GetSize();
}

int CollisionManager::GetHitboxArraySize()
{
	return (int) m_prgHitbox.GetSize();
}

DynamicArray<Entity*> CollisionManager::GetHitboxArray()
{
	return m_prgHitbox;
}

Entity* CollisionManager::GetHitboxArrayIndex(int nIndex)
{
	return m_prgHitbox[nIndex];
}