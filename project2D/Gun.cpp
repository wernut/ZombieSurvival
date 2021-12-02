#include "Gun.h"
#include "Input.h"
#include "Application.h"
#include "Player.h"
#include "Grid.h"
#include <iostream>

#define RAY_COUNT 30

Gun::Gun(Player* pPlayer, Level* pLevel) : Weapon(1, 50, 10, 50, 10)
{
	m_pPlayer = pPlayer;
	m_pLevel = pLevel;
	m_bHasShot = false;
	m_fCooldown = 10.0f;
	m_fCooldownMax = m_fCooldown;
	m_bReloading = false;
	m_nHitCount = 0;

	for (int i = 0; i < RAY_COUNT; ++i)
	{
		m_prgUnactive.PushBack(new Ray());
	}
}

Gun::~Gun()
{
	// Clean up.
	for (int i = 0; i < m_prgUnactive.GetSize(); ++i)
	{
		delete m_prgUnactive[i];
	}

	for (int i = 0; i < m_prgActive.GetSize(); ++i)
	{
		delete m_prgActive[i];
	}
}

void Gun::Update(float fDeltaTime)
{
	aie::Input* pInput = aie::Input::GetInstance();

	if (m_bHasShot)
	{
		m_fCooldown -= 200.0f * fDeltaTime;
		if (m_fCooldown <= 0)
		{
			m_fCooldown = m_fCooldownMax;
			m_bHasShot = false;
			m_pPlayer->SetFire(false);
		}
	}

	if (pInput->WasKeyReleased(aie::INPUT_KEY_SPACE) && m_fCooldown == m_fCooldownMax && m_nClipSize > 0)
	{
		Shoot(fDeltaTime);
	}

	if (m_nClipSize == 0)
	{
		// Reload(fDeltaTime);
		// - Will need to create a reload animation before completion.
		m_nAmmoCount -= 10;
		m_nClipSize += 10;
	}

	if (m_nAmmoCount == 0)
	{
		Refill();
	}
}

void Gun::Draw(aie::Renderer2D* pRenderer)
{
	// Draw active rays
	//for (int i = 0; i < m_prgActive.GetSize() - 1; ++i)
	//{
	//	m_prgActive[i]->Draw(pRenderer);
	//}

	if (m_bHasShot)
	{
		m_pPlayer->SetFire(true);
		pRenderer->SetRenderColour(1.0f, 1.0f, 0.0f, 0.5f);
		pRenderer->DrawLine(m_prgUnactive[0]->GetStartPoint().x, m_prgUnactive[0]->GetStartPoint().y, m_prgUnactive[0]->GetEndPoint().x, m_prgUnactive[0]->GetEndPoint().y, 2.0f);
		pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Base class draw function.
	GameObject::Draw(pRenderer);
}

void Gun::Shoot(float fDeltaTime)
{
	// Get some instances.
	CollisionManager* pCM = CollisionManager::GetInstance();
	aie::Input* pInput = aie::Input::GetInstance();
	aie::Application* pApp = aie::Application::GetInstance();

	// Get the window width and height.
	float fWindowWidth  = (float) pApp->GetWindowWidth();
	float fWindowHeight = (float) pApp->GetWindowHeight();

	// Get instance of the levels grid.
	Grid* pGrid = m_pLevel->GetGrid();

	// Clear node check list.
	m_prgNodeCheck.Clear();

	// Activate a ray so we can use it.
	m_prgActive.PushFront(m_prgUnactive[0]);
	m_prgUnactive.PopFront();

	// Starting point for ray.
	Vector2 v2StartPoint = GetPosition();
	Node* pCurrent = pGrid->GetNodeByPosition(v2StartPoint);

	// End point for ray.
	Vector2 v2Forward = m_pPlayer->GetGlobalTransform().getForward();
	Vector2 v2ProjectedPoint = v2StartPoint - (v2Forward * 10);
	Vector2 v2EndPoint = v2ProjectedPoint;
	Node* pEndNode = pGrid->GetNodeByPosition(v2EndPoint);

	// A vector we're going to seek with.
	Vector2 v2SearchPoint = v2StartPoint;

	// Check for solid nodes between the start and end point.
	m_prgActive[0]->SetPoints(v2StartPoint, v2EndPoint);
	Node* pPrevious = nullptr;
	bool bSearching = true;

	while (bSearching)
	{	
		// Check the search point is still inside the map.
		if (v2SearchPoint.x < 0 || v2SearchPoint.x > fWindowWidth &&
			v2SearchPoint.y < 0 || v2SearchPoint.y > fWindowHeight)
		{
			m_prgActive[0]->SetPoints(v2StartPoint, v2SearchPoint);
			break;
		}

		// Send ray.
	    Vector2 v2Direction = v2EndPoint - v2SearchPoint;
		v2SearchPoint += v2Direction * fDeltaTime;
		Node* v2Target = pGrid->GetNodeByPosition(v2SearchPoint);

		if (!pPrevious)
		{
			m_prgNodeCheck.PushBack(v2Target->m_v2Position);
			pPrevious = v2Target;
		}
		else if (v2Target->m_v2Position != pPrevious->m_v2Position)
		{
			m_prgNodeCheck.PushBack(v2Target->m_v2Position);
			pPrevious = v2Target;
		}

		if (v2Target->m_bBlocked)
		{
			m_prgActive[0]->SetPoints(v2StartPoint, v2SearchPoint);
			bSearching = false;
			break;
		}

		// Check for collision with hitboxes.
		for (int i = 0; i < pCM->GetHitboxArraySize(); ++i)
		{
			Entity* pTarget = pCM->GetHitboxArrayIndex(i);
			if (pTarget->GetHitbox() && pTarget->IsAlive())
			{
				if (m_prgActive[0]->IsPointInside(v2SearchPoint, pTarget->GetHitbox()))
				{
					Entity* pTarget = pCM->GetHitboxArrayIndex(i);
					m_prgActive[0]->SetPoints(v2StartPoint, v2SearchPoint);
					pTarget->TakeDamage((float) m_nDamage);
					pTarget->SetHasBeenShot(true);
					m_pPlayer->SetScore(m_pPlayer->GetScore() + 1);
					bSearching = false;
					break;
				}
			}
		}

		v2EndPoint += v2Direction * fDeltaTime;
	}
	// Deactivate the a ray.
	m_prgUnactive.PushFront(m_prgActive[0]);
	m_prgActive.PopFront();
	
	// Take one from the ammo count.
	--m_nClipSize;

	// Enable the has shot bool.
	m_bHasShot = true;
}