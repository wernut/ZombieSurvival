#include "Player.h"
#include "Input.h"
#include "Application.h"
#include "Gun.h"
#include <iostream>

Player::Player() : Entity(m_pTextureManager->ENTITY_PLAYER)
{
	m_rBounds = new Rectangle(GetPosition().x, GetPosition().x, 30.0f, 30.0f);
	pInv = new Inventory(Vector2(0, 0), Vector2(500, 350));
	m_eCurrentState = EPLAYERSTATE_IDLE;
	m_bRequiresSide = true;
	m_bShooting = false;
	m_pCurrentWeapon = nullptr;
	m_fMaxVelocity = 100.0f;
	m_nScore = 0;
}

Player::~Player()
{
	delete pInv;
	pInv = nullptr;
}

void Player::Update(float fDeltaTime)
{
	aie::Input* pInput = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = (float) pInput->GetMouseX();
	v2MousePos.y = (float) pInput->GetMouseY();

	Vector2 v2Position = GetPosition();
	m_fVelocity = 0.0f;
	if (pInput->IsKeyDown(aie::INPUT_KEY_W))
	{
		m_fVelocity = -m_fMaxVelocity;
	}

	if (pInput->IsKeyDown(aie::INPUT_KEY_S))
	{
		m_fVelocity = m_fMaxVelocity;
	}

	float fRotation = GetRotation();
	if (pInput->IsKeyDown(aie::INPUT_KEY_A))
	{
		fRotation += 2.5f * fDeltaTime;
	}

	if (pInput->IsKeyDown(aie::INPUT_KEY_D))
	{
		fRotation -= 2.5f * fDeltaTime;
	}
	SetRotation(fRotation);

	Vector2 v2Forward = GetGlobalTransform().getForward();
	v2Position += v2Forward * GetCurrentVelocity() * fDeltaTime;
	SetPosition(v2Position);

	this->UpdateBounds(v2Position);

	Entity::Update(fDeltaTime);
}

void Player::DrawState(aie::Renderer2D* &pRenderer, int &frame, float &size)
{
	switch (m_eCurrentState)
	{
	case EPLAYERSTATE_IDLE:
		DrawIdle(pRenderer, frame, size);
		break;

	case EPLAYERSTATE_MOVE:
		DrawMove(pRenderer, frame, size);
		break;

	case EPLAYERSTATE_SHOOT:
		DrawShoot(pRenderer, frame, size);
		break;

	case EPLAYERSTATE_RELOAD:
		DrawReload(pRenderer, frame, size);
		break;
	}
}

void Player::SwitchState(EPLAYERSTATE eNewState)
{
	m_eCurrentState = eNewState;
}

void Player::Draw(aie::Renderer2D* pRenderer)
{
	Entity::Draw(pRenderer);

	pRenderer->SetRenderColour(1.0f, m_fHitValue, m_fHitValue, 1.0f);

	// Get state information.
	int frame = 0;
	float size = 0;
	DrawState(pRenderer, frame, size);

	// Draw state.
	pRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	pRenderer->DrawSpriteTransformed3x3(m_pTexture, GetGlobalTransform(), 50.0f, 50.0f);
	pRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);

	if (frame >= 3)
		m_bShooting = false;
}

void Player::OnCollision(GameObject* pGameObject, int nSide)
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
	m_fVelocity = -m_fVelocity * fOffSet;
	SetPosition(v2Position);
}

void Player::DrawIdle(aie::Renderer2D* &pRenderer, int &frame, float &size)
{
	if (m_pTexture != m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER))
		m_pTexture = m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER);

	aie::Application* pApp = aie::Application::GetInstance();
	float time = pApp->GetTime();
	float animSpeed = 0.0f;
	frame = 0;
	size = 1.0f / 15.0f;

	if (GetCurrentVelocity() != 0)
		SwitchState(EPLAYERSTATE_MOVE);

	if (m_bShooting)
		SwitchState(EPLAYERSTATE_SHOOT);
}

void Player::DrawMove(aie::Renderer2D* &pRenderer, int &frame, float &size)
{
	if (m_pTexture != m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER))
		m_pTexture = m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER);

	aie::Application* pApp = aie::Application::GetInstance();
	float time = pApp->GetTime();
	float animSpeed = 20.0f;
	frame = ((int)(time * animSpeed) % 15);
	size = 1.0f / 15.0f;

	if (GetCurrentVelocity() == 0)
		SwitchState(EPLAYERSTATE_IDLE);

	if (m_bShooting)
		SwitchState(EPLAYERSTATE_SHOOT);
}

void Player::DrawShoot(aie::Renderer2D* &pRenderer, int &frame, float &size)
{
	if (m_pTexture != m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER_SHOOT))
		m_pTexture = m_pTextureManager->GetTexture(m_pTextureManager->ENTITY_PLAYER_SHOOT);

	aie::Application* pApp = aie::Application::GetInstance();
	float time = pApp->GetTime();
	float animSpeed = 10.0f;
	frame = ((int)(time * animSpeed) % 3);
	size = 1.0f / 3;

	if (!m_bShooting)
	{
		if (GetCurrentVelocity() == 0)
			SwitchState(EPLAYERSTATE_IDLE);
		else
			SwitchState(EPLAYERSTATE_MOVE);
	}
}

/* TODO: Create reloading animation. */
void Player::DrawReload(aie::Renderer2D* &pRenderer, int &frame, float &size){}

void Player::SetScore(int nScore)
{
	m_nScore = nScore;
}

int Player::GetScore()
{
	return m_nScore;
}

void Player::SetCurrentWeapon(Weapon* pWeapon)
{
	m_pCurrentWeapon = pWeapon;
}

Weapon* Player::GetCurrentWeapon()
{
	return m_pCurrentWeapon;
}

void Player::SetFire(bool bFire)
{
	m_bShooting = bFire;
}

Inventory* Player::GetInventory()
{
	return pInv;
}

