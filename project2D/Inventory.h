#pragma once
#include "DynamicArray.h"
#include "GameObject.h"
#include "Font.h"

class Inventory
{
protected:
	DynamicArray<GameObject*> m_prgSlots;
	int m_nMaxObjectCount;
	Vector2 m_v2Position;
	Vector2 m_v2Size;
	aie::Font* m_pFont;

public:
	Inventory(Vector2 v2Position, Vector2 v2Size);
	~Inventory();

	void Draw(aie::Renderer2D* pRenderer);
	void DrawTextureBox(aie::Renderer2D* pRenderer, int eTexture, Vector2 v2Position);
	void AddObject(GameObject* pObject);
	void RemoveObject(GameObject* pObject);
	GameObject* GetObject(int nIndex);
};

