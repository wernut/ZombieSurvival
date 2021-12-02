#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Rectangle.h"
#include <vector>

class GameObject
{
public:
	GameObject(char* szTag);
	GameObject(float fWidth, float fHeight, char* szTag);
	GameObject(const char* szTextureLocation, char* szTag);
	virtual ~GameObject();

	virtual void Update(float fDeltaTime);
	virtual void Draw(aie::Renderer2D* pRenderer);
	virtual void OnCollision(GameObject* pGameObject, int nSide = 0);
	void UpdateGlobalTransform();

	void SetVelocity(float fVelocity);
	float GetCurrentVelocity();

	void SetPosition(Vector2 v2Pos);
	void SetRotation(float radians);
	void SetScale(Vector2 v2Scale);
	void UpdateBounds(Vector2 v2Pos);
	Rectangle* GetBounds();

	/* Get global variables. */
	Vector2 GetPosition();
	float GetRotation();
	Vector2 GetScale();

	/* Get local variables.*/
	Vector2 GetLocalPosition();
	Vector2 GetLocalScale();
	float   GetLocalRotation();

	void SetParent(GameObject* pParent);
	GameObject* GetParent();

	Matrix3 GetLocalTransform();
	Matrix3 GetGlobalTransform();

	void SetColliding(bool bColliding);
	bool GetColliding();

	bool RequiresSide();

	const char* GetTag();

protected:
	Matrix3 m_m3LocalTransform;
	Matrix3 m_m3GlobalTransform;
	GameObject* m_pParent;
	std::vector<GameObject*> m_ChildList;
	aie::Texture* m_pTexture; 
	Rectangle* m_rBounds;
	float m_fVelocity;
	float m_fMaxVelocity;
	bool m_bRequiresSide;
	char m_szTag[64];

private:
	void AddChild(GameObject* pChild);
	void RemoveChild(GameObject* pChild);
	bool m_bIsColliding;
};

