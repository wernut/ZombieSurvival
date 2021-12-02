#include "Entity.h"

Entity::Entity(TextureManager::E_TEXTURES eTexture) : GameObject("Entity")
{
	m_pTextureManager = TextureManager::GetInstance();
	m_pTexture = m_pTextureManager->GetTexture(eTexture);
	m_nHealth = 10;
	m_nMaxHealth = m_nHealth;
	m_prHitbox = nullptr;
	m_bHasBeenHit = false;
	m_fHitValue = 1.0f;
	m_bIsAlive = true;
	m_bHasBeenShot = false;
	m_fCritcialHealth = (float) (m_nHealth / 4);
	m_bIsActive = false;
}

Entity::Entity(TextureManager::E_TEXTURES eTexture, Vector2 v2Scale) : GameObject("Entity")
{
	m_pTextureManager = TextureManager::GetInstance();
	m_pTexture = m_pTextureManager->GetTexture(eTexture);
	m_prHitbox = new Rectangle(GetPosition().x, GetPosition().y, v2Scale.x, v2Scale.y, false);
	m_nHealth = 10;
	m_nMaxHealth = m_nHealth;
	m_v2Scale = v2Scale;
	m_bHasBeenHit = false;
	m_fHitValue = 1.0f;
	m_bIsAlive = true;
	m_bHasBeenShot = false;
	m_fCritcialHealth = 2;
	m_bIsActive = false;
}

Entity::~Entity()
{
	m_pTexture = nullptr;
	m_pTextureManager = nullptr;

	if (m_prHitbox)
	{
		delete m_prHitbox;
		m_prHitbox = nullptr;
	}
}
void Entity::Update(float fDeltaTime)
{


	if (m_prHitbox)
		m_prHitbox->Update(GetPosition().x, GetPosition().y);

	if (m_bHasBeenHit)
	{
		if (m_fHitValue > 0.2f)
			m_fHitValue -= 5.0f * fDeltaTime;
		else
		{
			m_bHasBeenHit = false;
			m_fHitValue = 1.0f;
		}

	}

	GameObject::Update(fDeltaTime);
}

void Entity::Draw(aie::Renderer2D* pRenderer)
{

	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	GameObject::Draw(pRenderer);

	//if (m_rBounds)
	//	m_rBounds->Draw(pRenderer, 1.0, 0.0f, 0.0f, 0.5f);

	//if (m_prHitbox)
	//	m_prHitbox->Draw(pRenderer, 1.0, 0.0f, 0.0f, 0.2f);
}

void Entity::TakeDamage(float nAmount)
{
	m_nHealth -= (int) nAmount;
	m_bHasBeenHit = true;
	m_fVelocity -= 5.0f;
}

int Entity::GetHealth()
{
	return m_nHealth;
}

void Entity::SetStartPos(Vector2 v2StartPos)
{
	m_v2StartPos = v2StartPos;
}

void Entity::SetEndPos(Vector2 v2EndPos)
{
	m_v2EndPos = v2EndPos;
}

void Entity::SetAlive(bool bAlive)
{
	m_bIsAlive = bAlive;
}

bool Entity::IsAlive()
{
	return m_nHealth > 0;
}

Rectangle* Entity::GetHitbox()
{
	return m_prHitbox;
}

// This also sets the start point.
void Entity::SetSpawnPosition(Vector2 v2Position)
{
	m_v2SpawnPosition = v2Position;
	m_v2StartPos = v2Position;
}

Vector2 Entity::GetSpawnPosition()
{
	return m_v2SpawnPosition;
}

void Entity::SetHealth(int fHealth)
{
	m_nHealth = fHealth;
}

void Entity::SetMaxHealth(int nHealth)
{
	m_nMaxHealth = nHealth;
}

int Entity::GetMaxHealth()
{
	return m_nMaxHealth;
}

void Entity::SetHasBeenShot(bool bHasBeenShot)
{
	m_bHasBeenShot = bHasBeenShot;
}

bool Entity::GetHasBeenSot()
{
	return m_bHasBeenShot;
}


bool Entity::GetActive()
{
	return m_bIsActive;
}

void Entity::SetActive(bool bActive)
{
	m_bIsActive = bActive;
}
