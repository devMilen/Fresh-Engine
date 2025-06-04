#include "Collision.h"

F::F() : aUp(1.0f), aDown(1.0f), b(0.0f){}
F::F(float aUp, float aDown, float y) : aUp(aUp), aDown(aDown), b(b) {}

float F::Calc(float x)
{
	return aUp * x / aDown + b;
}

ColInfo::ColInfo() : isColliding(false), depth(0.0f), CollNormal(0.0f, 0.0f) {}
ColInfo::ColInfo(bool isColliding, float depth, const glm::vec2& CollNormal)
	: isColliding(isColliding), depth(depth), CollNormal(CollNormal) {};
