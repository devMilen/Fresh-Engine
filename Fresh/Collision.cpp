#include "Collision.h"

F::F() : aUp(1.0f), aDown(1.0f), m_b(0.0f){}
F::F(float aUp, float aDown, float y) : aUp(aUp), aDown(aDown), m_b(m_b) {}

float F::Calc(float x)
{
	return aUp * x / aDown + m_b;
}

ColInfo::ColInfo() : isColliding(false), m_dist_z(0.0f), CollNormal(0.0f, 0.0f) {}
ColInfo::ColInfo(bool isColliding, float m_dist_z, const glm::vec2& CollNormal)
	: isColliding(isColliding), m_dist_z(m_dist_z), CollNormal(CollNormal) {};
