#pragma once

#include "Renderer2D.h"
#include "Vector2.h"
#include "Rectangle.h"

class Ray
{
private:
	Vector2 m_v2StartPoint, m_v2EndPoint;

public:
	Ray(){}
	~Ray(){}

	void SetPoints(Vector2 v2StartPoint, Vector2 v2EndPoint)
	{
		m_v2StartPoint = v2StartPoint;
		m_v2EndPoint = v2EndPoint;
	}

	Vector2 GetStartPoint()
	{
		return m_v2StartPoint;
	}

	Vector2 GetEndPoint()
	{
		return m_v2EndPoint;
	}

	bool IsPointInside(Vector2 v2Point, Rectangle* pRect)
	{
		float otherX = pRect->m_x;
		float otherY = pRect->m_y;
		float otherWidth = pRect->m_width;
		float otherHeight = pRect->m_height;
		float otherX1 = otherX + otherWidth;
		float otherY1 = otherY + otherHeight;

		return (v2Point.x >= otherX && v2Point.x <= otherX1) &&
			   (v2Point.y >= otherY && v2Point.y <= otherY1);
	}

	void Update(float fDeltaTime){}

	void Draw(aie::Renderer2D* pRenderer)
	{
		pRenderer->DrawLine(m_v2StartPoint.x, m_v2StartPoint.y, m_v2EndPoint.x, m_v2EndPoint.y, 2.0f);
	}
};