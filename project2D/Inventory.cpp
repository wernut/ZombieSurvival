#include "Inventory.h"
#include "TextureManager.h"

Inventory::Inventory(Vector2 v2Position, Vector2 v2Size)
{
	m_v2Position = v2Position; 
	m_v2Size = v2Size;
	m_nMaxObjectCount = 5;
	m_pFont = new aie::Font("./font/consolas.ttf", 24);
}

Inventory::~Inventory()
{
	delete m_pFont;
	m_pFont = nullptr;
}

void Inventory::Draw(aie::Renderer2D* pRenderer)
{
	TextureManager* pTextureManager = TextureManager::GetInstance();

	// Draw inventory box.
	//pRenderer->SetRenderColour(0.5f, 0.5f, 0.5f, 0.5f);
	//pRenderer->DrawBox(m_v2Position.x, m_v2Position.y, m_v2Position.x + m_v2Size.x, m_v2Position.y + m_v2Size.y);
	//pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	Vector2 v2Position = m_v2Position;
	//v2Position.x = m_v2Position.x - 22.5f;
	//v2Position.y = v2Position.y + m_fHeight - 55.0f;
	// Draw textures.
	for (int i = 0; i < m_prgSlots.GetSize() - 1; ++i)
	{
		//if (i == pTextureManager->TILE_WOODPLANK + 1)
		//{
		//	v2Position.y -= (SQUARE_SIZE + 5.0f);
		//	v2Position.x = m_v2Position.x - 22.5f;
		//}
		v2Position.x += (SQUARE_SIZE + 5.0f);

		/*if (i == m_nSelectedTile)
			pRenderer->DrawBox(v2Position.x, v2Position.y, SQUARE_SIZE + 2.5f, SQUARE_SIZE + 2.5f);*/

		// Texture display.
		//DrawTextureBox(pRenderer, i, v2Position);
	}

	// TODO: Loop through all objects that are in the slot array and draw the texture to the box.
	//		 Set up the scroll wheel to scroll through items.
}

void Inventory::DrawTextureBox(aie::Renderer2D* pRenderer, int eTexture, Vector2 v2Position)
{
	// Get the texture manager.
	TextureManager* pTextureManager = TextureManager::GetInstance();
	pRenderer->DrawSprite(pTextureManager->GetTexture(eTexture), v2Position.x, v2Position.y, SQUARE_SIZE, SQUARE_SIZE);
}

void Inventory::AddObject(GameObject* pObject)
{
	m_prgSlots.PushBack(pObject);
}

void Inventory::RemoveObject(GameObject* pObject)
{
	m_prgSlots.Remove(pObject);
}

GameObject* Inventory::GetObject(int nIndex)
{
	return m_prgSlots[nIndex];
}
