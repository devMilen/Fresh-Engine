#pragma once
#include <iostream>
#include "Shape.h"
#include "Transform.h"

class Collision {
public:
	//SAT
	//for each side of both shapes
	//	find side's normal vec
	//	project both shapes onto an axis perpendicular to the normal vec
	//	if the projections overlap (1D collision)
	//		continue
	//	else return false 
	class F
	{
	public:
		float aUp, aDown, b;
		F();
		F(float aUp, float aDown, float b);

		float Calc(float x);
	};

	class Info
	{
	public:
		bool isColliding;
		float depth;
		glm::vec2 CollNormal;

		Info();
		Info(bool isColliding, float depth, const glm::vec2& CollNormal);
	};

	static Shape::Line Projected(const Shape::Def* shape, const Shape::Line& axis);

	static bool Check1D(const Shape::Line& proj1, const Shape::Line& proj2);

	static bool Check(const Shape::Def* shape, const Shape::Def* shape2);
	static Info CheckInfo(const Shape::Def* shape, const Shape::Def* shape2);

	static bool Check(Shape::Def* shape, const Transform& transform1, Shape::Def* shape2, const Transform& transform2);
	static Info CheckInfo(Shape::Def* shape, const Transform& transform1, Shape::Def* shape2, const Transform& transform2);

	static bool CheckScaleCir(Shape::Def* shape, const Shape::Circle& cir, const Transform& cirTransform);
	static bool CheckScaleCir(Shape::Def* shape, const Transform& shapeTransform, const Shape::Circle& cir, const Transform& cirTransform);

	static bool RayIntersectsSegment(
		const glm::vec2& rayOrigin, const glm::vec2& rayDir,
		const glm::vec2& segA, const glm::vec2& segB, glm::vec2* outIntersection = nullptr
	);
	static bool PinPoly(const glm::vec2& p, Shape::Def* shape);
	static bool PinPoly(float pX, float pY, Shape::Def* shape);
};
