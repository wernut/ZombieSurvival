#include "Zombie.h"
#include "Node.h"
#include "Application.h"
#define _USE_MATH_DEFINES
#include <random>
#include <iostream>
#include <math.h>
#include "Input.h"

Zombie::Zombie(Grid* pGrid, Player* pPlayer) : Entity(m_pTextureManager->ENTITY_ZOMBIE, Vector2(40.0f, 40.0f))
{
	// Objects
	m_pGrid = pGrid;
	m_pPlayer = pPlayer;
	m_rBounds = new Rectangle(GetPosition().x, GetPosition().x, 30.0f, 30.0f);

	// Conditions
	m_bHasAttacked = false;
	m_bIsSearching = false;
	m_bHasSeenPlayer = false;
	m_bRecalculate = true;
	m_bAnimation = true;
	m_bRequiresSide = true;
	for (int i = 0; i < DEBUG_COUNT; ++i)
		m_baDebugOptions[i] = false;

	// Properties
	m_eCurrentState = EAISTATE_SPAWN;
	m_fVelocity = 35.0f;
	m_fMaxVelocity = 85.0f;
	m_fSpeed = 85.0f;
	m_fSearchingSpeed = 50.0f;
	m_fDamage = 1.0f;
	m_fRangeOfAttack = 40.0f;
	m_fRangeOfSight = 175.0f;
	m_fRangeOfFlee = 200.0;

	// Utilites
	m_nNodePos = 0;
	m_nFrame = 0;
	m_nDebugOptions = 0;

	// Timers
	m_fTimer = 0.0f;
	m_fShotTimer = 0.0f;
	m_fAttackTimer = 0.0f;
	m_fMaxShotTimer = 10.0f;
	m_fMaxTimer = 100.0f;
	m_fTimerSpeed = 175.0f;
	m_fRegenTimer = 0.0f;
	m_fRegenSpeed = 200.0f;
}

Zombie::~Zombie()
{
	m_pGrid = nullptr;
}

void Zombie::Update(float fDeltaTime)
{
	// If the entity isn't active, then don't update it.
	if (!m_bIsActive)
		return;

	// Setting the end position for the path finding.
	this->m_v2EndPos = m_pPlayer->GetPosition();

	// If the zombie is alive and isn't in the spawn state:
	if (m_eCurrentState != EAISTATE_SPAWN && this->IsAlive())
	{
		// Adding movement to the zombie.
		float fAcceleration = m_fSpeed / 3;
		if (m_fVelocity < m_fMaxVelocity)
			m_fVelocity += fAcceleration * fDeltaTime;
	}

	// Updating the AI state.
	UpdateState(fDeltaTime);

	// Updating base class.
	Entity::Update(fDeltaTime);

	// Setting up the debug toggle.
	aie::Input* pInput = aie::Input::GetInstance();
	if (pInput->WasKeyPressed(aie::INPUT_KEY_1))
	{
		if (m_nDebugOptions < DEBUG_COUNT - 1)
			++m_nDebugOptions;
		else
			m_nDebugOptions = 0;

		for (int i = 0; i < m_nDebugOptions; ++i)
		{
			m_baDebugOptions[i] = true;
		}
	}

}

void Zombie::Draw(aie::Renderer2D* pRenderer)
{
	// If the entity isn't active, then don't update it.
	if (!m_bIsActive)
		return;

	// Only drawing the zombie if it is alive.
	if (this->IsAlive())
	{
		// Creating an overlay effect for damage.
		pRenderer->SetRenderColour(1.0f, m_fHitValue, m_fHitValue, 1.0f);

		// Drawing the animations.
		float fTime = aie::Application::GetInstance()->GetTime();
		switch (m_eCurrentState)
		{
		case EAISTATE_SEARCH:
			this->DrawAnimation(pRenderer, fTime, 18.0f, 15);
			break;

		case EAISTATE_CHASE:
			this->DrawAnimation(pRenderer, fTime, 18.0f, 15);
			break;

		case EAISTATE_ATTACK:
			this->DrawAnimation(pRenderer, fTime, 18.0f, 9);
			break;

		case EAISTATE_FLEE:
			this->DrawAnimation(pRenderer, fTime, 18.0f, 15);
			break;
		}
	}
	// Drawing the base class.
	Entity::Draw(pRenderer);
}

void Zombie::DrawAnimation(aie::Renderer2D* &pRenderer, float &fTime, float animSpeed, int frameCount)
{
	// Animation
	int frame = ((int)(fTime * animSpeed) % frameCount);
	float size = 1.0f / frameCount;
	pRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	pRenderer->DrawSpriteTransformed3x3(m_pTexture, GetGlobalTransform(), 55.0f, 55.0f);
	pRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);

	// Draw debug information.
	this->DrawDebugInformation(pRenderer);
}

void Zombie::DrawDebugInformation(aie::Renderer2D* pRenderer)
{
	if (m_baDebugOptions[0])
	{
		// Path lines
		if (m_rgPath.size() > 1)
		{
			// Drawing the path lines.
			pRenderer->SetRenderColour(0.0f, 0.0f, 1.0f, 1.0f);
			for (int i = 1; i < m_rgPath.size(); ++i)
			{
				pRenderer->DrawLine(m_rgPath[i - 1].x, m_rgPath[i - 1].y, m_rgPath[i].x, m_rgPath[i].y, 5.0f);
			}
		}
	}

	if (m_baDebugOptions[1])
	{
		// Range of flee
		Vector2 v2Position = GetPosition();
		pRenderer->SetRenderColour(0.0f, 1.0f, 0.0f, 0.2f);
		pRenderer->DrawCircle(v2Position.x, v2Position.y, this->m_fRangeOfFlee);
		pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

		// Range of sight
		pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f, 0.2f);
		pRenderer->DrawCircle(v2Position.x, v2Position.y, this->m_fRangeOfSight);
		pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

		// Range of attack
		pRenderer->SetRenderColour(0.0f, 0.0f, 1.0f, 0.2f);
		pRenderer->DrawCircle(v2Position.x, v2Position.y, this->m_fRangeOfAttack);
		pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (m_baDebugOptions[1])
	{
		// Last known location:
		if (m_bHasSeenPlayer)
		{
			pRenderer->SetRenderColour(0.0f, 1.0f, 1.0f, 0.2f);
			pRenderer->DrawCircle(m_v2LastKnownLocation.x, m_v2LastKnownLocation.y, 15.0f);
			pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
}

void Zombie::UpdateState(float fDeltaTime)
{
	// If the zombie dies in any state, then switch to the death state.
	if (!this->IsAlive())
		m_eCurrentState = EAISTATE_DEATH;

	// else if the health drops below critical range, then enter the flee state.
	else if (this->GetHealth() <= m_fCritcialHealth)
		m_eCurrentState = EAISTATE_FLEE;

	// else if the zombie gets hit by the player, then they instantly find a path towards them.
	else if (this->GetHasBeenSot())
	{
		m_eCurrentState = EAISTATE_CHASE;
		m_fShotTimer += fDeltaTime;
		if (m_fShotTimer >= m_fMaxShotTimer)
		{
			this->SetHasBeenShot(false);
			m_fShotTimer = 0;
		}
	}

	// Switch case for the current state:
	switch (m_eCurrentState)
	{
	case EAISTATE_SPAWN:
		SpawnIn(fDeltaTime);
		break;

	case EAISTATE_SEARCH:
		Search(fDeltaTime);
		break;

	case EAISTATE_CHASE:
		Chase(fDeltaTime);
		break;

	case EAISTATE_ATTACK:
		Attack(fDeltaTime);
		break;

	case EAISTATE_FLEE:
		Flee(fDeltaTime);
		break;

	case EAISTATE_DEATH:
		Death(fDeltaTime);
		break;

	}
}

void Zombie::SpawnIn(float fDeltaTime)
{
	// Making sure the zombie is set alive and active
	this->m_bIsAlive = true;

	// Reset the zombie's health.
	this->SetHealth(m_nMaxHealth);

	// Set the position of the zombie.
	this->SetPosition(m_v2SpawnPosition);

	// Setting the end position for the path finding.
	this->m_v2EndPos = m_pPlayer->GetPosition();

	// Clearing the zombies path.
	this->m_rgPath.clear();

	// Resetting the shot lock and seen player bools.
	this->SetHasBeenShot(false);
	this->m_bHasSeenPlayer = false;
	this->m_bIsSearching = false;

	// Switching the zombie to search mode.
	this->m_eCurrentState = EAISTATE_SEARCH;
}

void Zombie::Search(float fDeltaTime)
{
	// Changing the animation texture.
	this->ChangeTexture(TextureManager::ENTITY_ZOMBIE);

	// Reducing the movement speed to the search speed.
	if (m_fSpeed != m_fSearchingSpeed)
		m_fSpeed = m_fSearchingSpeed;

	// Getting a random node.
	if (!m_bIsSearching)
	{
		// If the zombie has spotted the player, then they search towards that last known location.
		Node* pNode = nullptr;
		if (m_bHasSeenPlayer)
		{
			pNode = m_pGrid->GetNodeByPosition(m_v2LastKnownLocation);
		}
		else
		{
			aie::Application* pApp = aie::Application::GetInstance();
			int randX = (int) (rand() % pApp->GetWindowWidth());
			int randY = (int) (rand() % pApp->GetWindowHeight());
			pNode = m_pGrid->GetNodeByPosition(Vector2((float) randX, (float) randY));
		}

		// Finding a path to the random node.
		if (m_pGrid->FindPath(m_v2StartPos, pNode->m_v2Position, m_rgPath))
		{
			if (!m_bRecalculate)
				m_bRecalculate = true;

			m_bIsSearching = true;
		}
	}

	// Moving along the path found.
	MoveAlongPath(fDeltaTime);

	// Checking if the zombie is in range of sight.
	if (this->IsInRange(m_fRangeOfSight, m_v2EndPos))
		m_eCurrentState = EAISTATE_CHASE;
}

void Zombie::Chase(float fDeltaTime)
{
	// If the player is not in the line of sight, then go back to searching.
	if (!this->IsInRange(m_fRangeOfSight, m_v2EndPos))
		m_eCurrentState = EAISTATE_SEARCH;
	else
		m_v2LastKnownLocation = m_pPlayer->GetPosition();

	// Making sure the texture for the animation is correct.
	this->ChangeTexture(TextureManager::ENTITY_ZOMBIE);

	// Making sure the speed is correct.
	if (m_fSpeed != m_fMaxVelocity)
		m_fSpeed = m_fMaxVelocity;

	// Finding a path for the zombie.
	if (m_pGrid->FindPath(m_v2StartPos, m_v2EndPos, m_rgPath))
	{
		if (!m_bRecalculate)
			m_bRecalculate = true;
	}

	// Moving along the path found.
	MoveAlongPath(fDeltaTime);

	// Checking if the zombie is in range of attack.
	if (this->IsInRange(m_fRangeOfAttack, m_v2EndPos))
		m_eCurrentState = EAISTATE_ATTACK;
}

void Zombie::Death(float fDeltaTime)
{
	// Unactivating the zombie.
	this->m_bIsAlive = false;
}

void Zombie::Attack(float fDeltaTime)
{
	// Changing the animation texture.
	this->ChangeTexture(TextureManager::ENTITY_ZOMBIEATTACK);

	if (IsInRange(m_fRangeOfAttack, m_pPlayer->GetPosition()))
	{
		// Attacking the player and enabling the movement and attack cooldown.
		if (!m_bHasAttacked)
		{
			m_pPlayer->TakeDamage(m_fDamage);
				m_bHasAttacked = true;
		}
		else
		{
			// Cooldown.
			m_fAttackTimer += m_fTimerSpeed * fDeltaTime;

			// Stopping movement.
			this->m_fVelocity = 0.0f;

			// Checking if the timer has finished and reseting the attack.
			if (m_fAttackTimer >= m_fMaxTimer)
			{
				m_bHasAttacked = false;
				m_fAttackTimer = 0;
			}
		}
	}
	else
		m_eCurrentState = EAISTATE_CHASE;
}

void Zombie::Flee(float fDeltaTime)
{
	if (IsInRange(m_fRangeOfFlee, m_pPlayer->GetPosition())) // && HEALTH CRIT
	{
		Vector2 v2Position = GetPosition();
		Vector2 v2Direction = (v2Position - m_pPlayer->GetPosition());
		v2Direction.normalise();
		Vector2 v2ProjectedTarget = v2Position + (v2Direction * m_fSpeed);
		this->RotateAndSeek(v2ProjectedTarget, fDeltaTime);

		int nHealth = GetHealth();
		m_fRegenTimer += fDeltaTime;
		SetHealth(nHealth + (m_fRegenTimer / 2));

		if (nHealth == m_nMaxHealth)
		{
			m_eCurrentState = EAISTATE_SEARCH;
			m_fRegenTimer = 0;
		}
	}
}

bool Zombie::IsInRange(float fRange, Vector2 v2TargetPos)
{
	Vector2 v2Position = GetPosition();
	float fDist = (v2TargetPos - v2Position).magnitude();
	bool result = (fDist < fRange) ? true : false;
	return result;
}

void Zombie::RotateAndSeek(Vector2 v2Target, float fDeltaTime)
{
	// Getting the angle to the target.
	Vector2 v2Position = GetPosition();
	Vector2 v2Relative = v2Target - v2Position;
	float fAngleRadians = -atan2(v2Relative.x, v2Relative.y);

	// Setting the rotation.
	float fRotation = GetLocalRotation();
	fRotation = fAngleRadians;
	SetRotation(fRotation);

	// Moving foward towards the target.
	Vector2 v2Forward = GetGlobalTransform().getForward();
	v2Position += v2Forward * GetCurrentVelocity() * fDeltaTime;
	SetPosition(v2Position);
}

void Zombie::ChangeTexture(TextureManager::E_TEXTURES eTexture)
{
	if (m_pTexture != m_pTextureManager->GetTexture(eTexture))
		m_pTexture = m_pTextureManager->GetTexture(eTexture);
}

// Path must be set before using this!
void Zombie::MoveAlongPath(float fDeltaTime)
{
	// Checking if the path is set.
	if (m_rgPath.size() > 1)
	{
		// Getting the zombie's position and setting it to be the start point.
		Vector2 v2Position = GetPosition();
		m_v2StartPos = v2Position;

		// Making sure the node pos index doesn't go out of bounds.
		if (m_nNodePos >= m_rgPath.size() - 1)
		{
			m_nNodePos = (int)m_rgPath.size() - 1;
			m_bIsSearching = false;
		}

		// Getting the destination from the path array with the node pos index.
		Vector2 v2Dest = m_rgPath[m_nNodePos];
		this->RotateAndSeek(v2Dest, fDeltaTime);

		// Checking if the zombie is close enough to the node to change the node pos index.
		if ((v2Dest - v2Position).magnitude() < 1.0f)
		{
			m_nNodePos++;
			m_bRecalculate = true;
		}
	}
}

void Zombie::OnCollision(GameObject* pGameObject, int nSide)
{
	Vector2 v2Position = GetPosition();
	float fOffSet = 15.5f;
	switch (nSide)
	{
	case 0:
		v2Position.y = pGameObject->GetBounds()->m_rectUp + fOffSet;
		break;

	case 1:
		v2Position.x = pGameObject->GetBounds()->m_rectRight + fOffSet;
		break;

	case 2:
		v2Position.y = pGameObject->GetBounds()->m_rectDown - fOffSet;
		break;

	case 3:
		v2Position.x = pGameObject->GetBounds()->m_rectLeft - fOffSet;
		break;
	}
	m_fVelocity = 0;
	SetPosition(v2Position);
}

void Zombie::SetAlive(bool bAlive)
{
	if (bAlive)
	{
		m_eCurrentState = EAISTATE_SPAWN;
		m_bIsActive = true;
		SpawnIn(0.0f);
	}
	else
	{
		m_eCurrentState = EAISTATE_DEATH;
		m_bIsActive = false; 
	}
}