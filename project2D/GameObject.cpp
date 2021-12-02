#include "GameObject.h"
#include "Application.h"
#include "CollisionManager.h"

// Default constructor.
GameObject::GameObject(char* szTag)
{
	m_pTexture = nullptr;
	m_pParent = nullptr;
	m_rBounds = nullptr;
	m_bIsColliding = false;
	m_fVelocity = 0.0f;
	m_fMaxVelocity = 50.0f;
	m_bRequiresSide = false;
	strcpy_s(m_szTag, szTag);
}

// Construct to create a game object with physics.
GameObject::GameObject(float fWidth, float fHeight, char* szTag)
{
	m_pTexture = nullptr;
	m_pParent = nullptr;
	m_rBounds = new Rectangle(GetPosition().x, GetPosition().y, fWidth, fHeight);
	m_bIsColliding = false;
	m_fVelocity = 0.0f;
	m_fMaxVelocity = 50.0f;
	m_bRequiresSide = false;
	strcpy_s(m_szTag, szTag);
}

// Constructor to create an object with a texture and no bounds.
GameObject::GameObject(const char* szTextureLocation, char* szTag)
{
	m_pTexture = new aie::Texture(szTextureLocation);
	m_pParent = nullptr;
	m_rBounds = nullptr;
	m_bIsColliding = false;
	m_fVelocity = 0.0f;
	m_fMaxVelocity = 50.0f;
	m_bRequiresSide = false;
	strcpy_s(m_szTag, szTag);
}

GameObject::~GameObject()
{
	for (GameObject* pChild : m_ChildList)
	{
		delete pChild;
	}

	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_rBounds)
	{
		delete m_rBounds;
		m_rBounds = nullptr;
	}
}

void GameObject::UpdateBounds(Vector2 v2Pos)
{
	m_rBounds->Update(v2Pos.x, v2Pos.y);
}

void GameObject::Update(float fDeltaTime)
{
	// Updating the bounds.
	if (m_rBounds)
		UpdateBounds(GetPosition());

	// Updating the children.
	for (GameObject* pChild : m_ChildList)
	{
		pChild->Update(fDeltaTime);
	}
}

void GameObject::Draw(aie::Renderer2D* pRenderer)
{
	// Render the default texture.
	//if (m_pTexture)
	//	pRenderer->DrawSpriteTransformed3x3(m_pTexture, m_m3GlobalTransform);

	for (GameObject* pChild : m_ChildList)
	{
		pChild->Draw(pRenderer);
	}

	// Render the bounds.
	//if (m_rBounds)
	//	m_rBounds->Draw(pRenderer, 1.0f, 0.0f, 0.0f, 0.2f);
}

void GameObject::OnCollision(GameObject* pGameObject, int nSide)
{}

void GameObject::SetVelocity(float fVelocity)
{
	m_fVelocity = fVelocity;
}

float GameObject::GetCurrentVelocity()
{
	return m_fVelocity;
}

void GameObject::UpdateGlobalTransform()
{
	if (m_pParent)
		m_m3GlobalTransform = m_pParent->m_m3GlobalTransform * m_m3LocalTransform;
	else
		m_m3GlobalTransform = m_m3LocalTransform;

	for (GameObject* pChild : m_ChildList)
	{
		pChild->UpdateGlobalTransform();
	}
}

void GameObject::SetPosition(Vector2 v2Pos)
{
	m_m3LocalTransform.setTranslation(v2Pos);
	UpdateGlobalTransform();
}


void GameObject::SetRotation(float fRadians)
{
	m_m3LocalTransform.setRotateZ(fRadians);
	UpdateGlobalTransform();
}

void GameObject::SetScale(Vector2 v2Scale)
{
	m_m3LocalTransform.setScale(v2Scale);
	UpdateGlobalTransform();
}

Vector2 GameObject::GetScale()
{
	return m_m3GlobalTransform.getScale();
}

Vector2 GameObject::GetPosition()
{
	return m_m3GlobalTransform.getTranslation();
}
float GameObject::GetRotation()
{
	return m_m3GlobalTransform.getRotation();
}

Vector2 GameObject::GetLocalScale()
{
	return m_m3LocalTransform.getScale();
}

Vector2 GameObject::GetLocalPosition()
{
	return m_m3LocalTransform.getTranslation();
}
float GameObject::GetLocalRotation()
{
	return m_m3LocalTransform.getRotation();
}

void GameObject::AddChild(GameObject* pChild)
{
	m_ChildList.push_back(pChild);
}

void GameObject::RemoveChild(GameObject* pChild)
{
	auto iter = std::find(m_ChildList.begin(), m_ChildList.end(), pChild);
	if (iter != m_ChildList.end())
	{
		m_ChildList.erase(iter);
	}
}

void GameObject::SetParent(GameObject* pParent)
{
	if (m_pParent)
		m_pParent->RemoveChild(this);

	m_pParent = pParent;

	if(pParent)
		m_pParent->AddChild(this);
}

GameObject* GameObject::GetParent()
{
	return m_pParent;
}

Rectangle* GameObject::GetBounds()
{
	return m_rBounds;
}

Matrix3 GameObject::GetLocalTransform()
{
	return m_m3LocalTransform;
}

Matrix3 GameObject::GetGlobalTransform()
{
	return m_m3GlobalTransform;
}

void GameObject::SetColliding(bool bColliding)
{
	m_bIsColliding = bColliding;
}

bool GameObject::GetColliding()
{
	return m_bIsColliding;
}

bool GameObject::RequiresSide()
{
	return m_bRequiresSide;
}


const char* GameObject::GetTag()
{
	return m_szTag;
}