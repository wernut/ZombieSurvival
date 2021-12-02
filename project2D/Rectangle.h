#pragma once

#include "Renderer2D.h"
#include "Vector2.h"

#define LINE_COUNT 4

class Rectangle
{
public:
	float m_x, m_y, m_width, m_height;
	float m_offset;
	bool m_active;
	bool m_activeLines[LINE_COUNT];
	float m_rectLeft, m_rectUp, m_rectRight, m_rectDown;

	Rectangle(float x, float y, float width, float height, bool active = true)
	{
		m_width = width;
		m_height = height;
		m_x = x - (m_width / 2);
		m_y = y - (m_height / 2);
		m_offset = 5.0f;
		m_active = active;
		for (int i = 0; i < LINE_COUNT; ++i)
			m_activeLines[i] = m_active;
	}

	~Rectangle() {}

	void SetActiveLine(int nIndex, bool bToggle)
	{
		m_activeLines[nIndex] = bToggle;
	}

	void Update(float x, float y)
	{
		m_x = x - (m_width / 2);
		m_y = y - (m_height / 2);
		m_rectLeft = m_x;
		m_rectDown = m_y;
		m_rectRight = m_x + m_width;
		m_rectUp = m_y + m_height;
	}

	bool IsInside(Rectangle* pRect)
	{
		float otherX = pRect->m_x;
		float otherY = pRect->m_y;
		float otherWidth = pRect->m_width;
		float otherHeight = pRect->m_height;
		float otherX1 = otherX + otherWidth;
		float otherY1 = otherY + otherHeight;

		return (m_x >= otherX || m_x <= otherX1) &&
			(m_y >= otherY || m_y <= otherY1);
	}

	bool Intersects(Rectangle* pRect)
	{
		float tw = m_width;
		float th = m_height;
		float rw = pRect->m_width;
		float rh = pRect->m_height;
		float tx = m_x;
		float ty = m_y;;
		float rx = pRect->m_x;
		float ry = pRect->m_y;
		rw += rx;
		rh += ry;
		tw += tx;
		th += ty;
		return ((rw < rx || rw > tx) &&
				(rh < ry || rh > ty) &&
				(tw < tx || tw > rx) &&
				(th < ty || th > ry));
	}
	
	// Returns an int based on what line on the rect is intersecting.
	// 0 = Down colliding with up.
	// 1 = Left colliding with right.
	// 2 = Up colliding with down.
	// 3 = Right colliding with left
	// -1 = Nothing is colliding.
	int LineInterects(Rectangle* pRect)
	{
		if (m_activeLines[0])
		{
			// Down side colliding with up.
			if (m_y < pRect->m_rectUp && m_y > pRect->m_rectUp - m_offset
				&& m_x < pRect->m_rectRight && m_rectRight > pRect->m_x)
				return 0;
		}

		if (m_activeLines[1])
		{
			// Left side colliding with Right.
			if (m_rectLeft < pRect->m_rectRight && m_rectLeft > pRect->m_rectRight - m_offset
				&& m_y < pRect->m_rectUp && m_rectUp > pRect->m_y)
				return 1;
		}

		if (m_activeLines[2])
		{
			// Up side colliding with down.
			if (m_rectUp > pRect->m_y && m_rectUp < pRect->m_y + m_offset
				&& m_x < pRect->m_rectRight && m_rectRight > pRect->m_x)
				return 2;
		}

		if (m_activeLines[3])
		{
			// Right side colliding with left.
			if (m_rectRight > pRect->m_rectLeft && m_rectRight < pRect->m_rectLeft + m_offset
				&& m_y < pRect->m_rectUp && m_rectUp > pRect->m_y)
				return 3;
		}

		// Not colliding.
		return -1;
	}

	float GetX()
	{
		return m_x;
	}

	float GetY()
	{
		return m_y;
	}

	void MoveX(int increment, float deltaTime)
	{
		m_x += increment * deltaTime;
	}

	void MoveY(int increment, float deltaTime)
	{
		m_y += increment * deltaTime;
	}

	void Draw(aie::Renderer2D* renderer, float r, float g, float b, float a)
	{
		renderer->SetRenderColour(r, g, b, a);
		if (m_active)
		{
			// Bottom
			if (m_activeLines[0])
				renderer->DrawLine(m_rectLeft, m_rectDown, m_rectRight, m_rectDown, m_offset);
			// Left
			if (m_activeLines[1])
				renderer->DrawLine(m_rectLeft, m_rectDown, m_rectLeft, m_rectUp, m_offset);
			// Top
			if (m_activeLines[2])
				renderer->DrawLine(m_rectLeft, m_rectUp, m_rectRight, m_rectUp, m_offset);
			// Right
			if (m_activeLines[3])
				renderer->DrawLine(m_rectRight, m_rectDown, m_rectRight, m_rectUp, m_offset);
		}
		else
			renderer->DrawBox(m_x + (m_width / 2), m_y + (m_height / 2), m_width, m_height);

		renderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}
};