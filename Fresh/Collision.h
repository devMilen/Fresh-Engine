#pragma once
#include <iostream>
#include "Shape.h"
#include "Transform.h"

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
		float aUp, aDown, m_b;
		F();
		F(float aUp, float aDown, float m_b);

		float Calc(float x);
};

class ColInfo
{
	public:
		bool isColliding;
		float m_dist_z;
		glm::vec2 CollNormal;

		ColInfo();
		ColInfo(bool isColliding, float m_dist_z, const glm::vec2& CollNormal);
};

inline glm::vec2 ProjectedP(const glm::vec2& P, const glm::vec2& A, const glm::vec2& d)
{
	glm::vec2 AP = P - A;
	float t = glm::dot(AP, d) / glm::dot(d, d);
	return A + t * d;
}
inline glm::vec2 ProjectedP(const glm::vec2& P, const Shape::Line& axis)
{
	return ProjectedP(P, axis.points[0], axis.points[1] - axis.points[0]);
}

inline Shape::Line LineProjected(const Shape::Def* shape, const Shape::Line& axis)
{
	glm::vec2 axisOrigin = axis.points[0];
	glm::vec2 axisDir = glm::normalize(axis.points[1] - axis.points[0]);

	const Shape::Circle* cir = dynamic_cast<const Shape::Circle*>(shape);
	if (cir)
	{
		glm::vec2 center = shape->points[0];
		float centerProjection = glm::dot(center - axisOrigin, axisDir);
		glm::vec2 res(centerProjection - cir->m_r, centerProjection + cir->m_r);

		glm::vec2 minPoint = axisOrigin + axisDir * res.x;
		glm::vec2 maxPoint = axisOrigin + axisDir * res.y;

		return Shape::Line(minPoint, maxPoint);
	}

	float minProj = FLT_MAX, maxProj = -FLT_MAX;

	for (int i = 0; i < shape->pointsSize(); ++i)
	{
		glm::vec2 relative = shape->points[i] - axisOrigin;
		float projection = glm::dot(relative, axisDir);

		minProj = std::min(minProj, projection);
		maxProj = std::max(maxProj, projection);
	}

	glm::vec2 minPoint = axisOrigin + axisDir * minProj;
	glm::vec2 maxPoint = axisOrigin + axisDir * maxProj;

	return Shape::Line(minPoint, maxPoint);
}
inline Shape::Line LineProjected(const Shape::Def* shape, const glm::vec2 P, const glm::vec2& dirVec)
{
	glm::vec2 axisOrigin = P;
	glm::vec2 axisDir = glm::normalize(dirVec);

	const Shape::Circle* cir = dynamic_cast<const Shape::Circle*>(shape);
	if (cir)
	{
		glm::vec2 center = shape->points[0];
		float centerProjection = glm::dot(center - axisOrigin, axisDir);
		glm::vec2 res(centerProjection - cir->m_r, centerProjection + cir->m_r);

		glm::vec2 minPoint = axisOrigin + axisDir * res.x;
		glm::vec2 maxPoint = axisOrigin + axisDir * res.y;

		return Shape::Line(minPoint, maxPoint);
	}

	float minProj = FLT_MAX, maxProj = -FLT_MAX;

	for (int i = 0; i < shape->pointsSize(); ++i)
	{
		glm::vec2 relative = shape->points[i] - axisOrigin;
		float projection = glm::dot(relative, axisDir);

		minProj = std::min(minProj, projection);
		maxProj = std::max(maxProj, projection);
	}
	glm::vec2 minPoint = axisOrigin + axisDir * minProj;
	glm::vec2 maxPoint = axisOrigin + axisDir * maxProj;

	return Shape::Line(minPoint, maxPoint);
}

inline glm::vec2 Projected(const Shape::Def* shape, const Shape::Line& axis)
{
	glm::vec2 axisOrigin = axis.points[0];
	glm::vec2 axisDir = glm::normalize(axis.points[1] - axis.points[0]);

	const Shape::Circle* cir = dynamic_cast<const Shape::Circle*>(shape);
	if (cir) {
		glm::vec2 center = shape->points[0];
		float centerProjection = glm::dot(center - axisOrigin, axisDir);
		return glm::vec2(centerProjection - cir->m_r, centerProjection + cir->m_r);
	}

	float minProj = FLT_MAX, maxProj = -FLT_MAX;

	for (int i = 0; i < shape->pointsSize(); ++i)
	{
		glm::vec2 relative = shape->points[i] - axisOrigin;
		float projection = glm::dot(relative, axisDir);

		minProj = std::min(minProj, projection);
		maxProj = std::max(maxProj, projection);
	}

	return glm::vec2(minProj, maxProj);
}
inline glm::vec2 Projected(const Shape::Def* shape, const glm::vec2 P, const glm::vec2& dirVec)
{
	glm::vec2 axisOrigin = P;
	glm::vec2 axisDir = glm::normalize(dirVec);

	const Shape::Circle* cir = dynamic_cast<const Shape::Circle*>(shape);
	if (cir) 
	{
		glm::vec2 center = shape->points[0];
		float centerProjection = glm::dot(center - axisOrigin, axisDir);
		return glm::vec2(centerProjection - cir->m_r, centerProjection + cir->m_r);
	}

	float minProj = FLT_MAX, maxProj = -FLT_MAX;

	for (int i = 0; i < shape->pointsSize(); ++i)
	{
		glm::vec2 relative = shape->points[i] - axisOrigin;
		float projection = glm::dot(relative, axisDir);

		minProj = std::min(minProj, projection);
		maxProj = std::max(maxProj, projection);
	}
	return glm::vec2(minProj, maxProj);
}

inline bool ProjectionsColliding(const glm::vec2& proj1, const glm::vec2& proj2)
{
	return !(proj1.y < proj2.x || proj1.x > proj2.y);
}

inline bool Colliding(const Shape::Def* shape1, const Shape::Def* shape2)
{
	if (shape1->Type() == Shape::Types::ShapeCircle &&
		shape2->Type() == Shape::Types::ShapeCircle)
	{
		const auto* c1 = dynamic_cast<const Shape::Circle*>(shape1);
		const auto* c2 = dynamic_cast<const Shape::Circle*>(shape2);
		if (c1 && c2) {
			glm::vec2 center1 = shape1->points[0];
			glm::vec2 center2 = shape2->points[0];
			float distSq = glm::dot(center1 - center2, center1 - center2);
			float radiusSum = c1->m_r + c2->m_r;
			return distSq <= radiusSum * radiusSum;
		}
	}

	auto edgeNormal = [](const glm::vec2& m_a, const glm::vec2& m_b) -> glm::vec2 {
		glm::vec2 edge = m_b - m_a;
		return glm::normalize(glm::vec2(-edge.y, edge.x));
	};

	const Shape::Def* shapes[] = { shape1, shape2 };

	for (int s = 0; s < 2; ++s)
	{
		const Shape::Def* shape = shapes[s];
		if (shape->Type() == Shape::Types::ShapeCircle) break;
		int pointCount = shape->pointsSize();

		for (int i = 0; i < pointCount; ++i)
		{
			glm::vec2 p1 = shape->points[i];
			glm::vec2 p2 = shape->points[(i + 1) % pointCount]; 
			glm::vec2 axis = edgeNormal(p1, p2);

			glm::vec2 proj1 = Projected(shape1, p1, axis);
			glm::vec2 proj2 = Projected(shape2, p1, axis);

			if (!ProjectionsColliding(proj1, proj2))
				return false;
		}
	}
	return true;
}
inline bool Colliding(Shape::Def* shape1, const Transform& tf1, Shape::Def* shape2, const Transform& tf2)
{
	shape1->Move(tf1.pos);
	shape1->Rotate(tf1.rotation);
	shape1->Scale(tf1.scale);

	shape2->Move(tf2.pos);
	shape2->Rotate(tf2.rotation);
	shape2->Scale(tf2.scale);

	bool colliding = Colliding(shape1, shape2);

	shape1->Scale(1.0f/tf1.scale);
	shape1->Rotate(-tf1.rotation);
	shape1->Move(-tf1.pos);

	shape2->Scale(1.0f/tf2.scale);
	shape2->Rotate(-tf2.rotation);
	shape2->Move(-tf2.pos);

	return colliding;
}

inline ColInfo CollidingInfo(const Shape::Def* shape1, const Shape::Def* shape2)
{
	auto edgeNormal = [](const glm::vec2& m_a, const glm::vec2& m_b) -> glm::vec2 {
		glm::vec2 edge = m_b - m_a;
		return glm::normalize(glm::vec2(-edge.y, edge.x));
		};

	const Shape::Def* shapes[] = { shape1, shape2 };
	float minDepth = std::numeric_limits<float>::max();
	glm::vec2 minAxis;

	for (int s = 0; s < 2; ++s)
	{
		const Shape::Def* shape = shapes[s];
		if (shape->Type() == Shape::Types::ShapeCircle) break;
		int pointCount = shape->pointsSize();

		for (int i = 0; i < pointCount; ++i)
		{
			glm::vec2 p1 = shape->points[i];
			glm::vec2 p2 = shape->points[(i + 1) % pointCount];
			glm::vec2 axis = edgeNormal(p1, p2);

			glm::vec2 proj1 = Projected(shape1, p1, axis);
			glm::vec2 proj2 = Projected(shape2, p1, axis);

			if (!ProjectionsColliding(proj1, proj2))
				return ColInfo(false, 0.0f, glm::vec2(0.0f));

			float overlap = std::min(proj1.y, proj2.y) - std::max(proj1.x, proj2.x);
			if (overlap < minDepth)
			{
				minDepth = overlap;
				minAxis = axis;
			}
		}
	}

	return ColInfo(true, minDepth, minAxis);
}
inline ColInfo CollidingInfo(Shape::Def* shape1, const Transform& tf1, Shape::Def* shape2, const Transform& tf2)
{
	shape1->Move(tf1.pos);
	shape1->Rotate(tf1.rotation);
	shape1->Scale(tf1.scale);

	shape2->Move(tf2.pos);
	shape2->Rotate(tf2.rotation);
	shape2->Scale(tf2.scale);

	ColInfo colliding = CollidingInfo(shape1, shape2);

	shape1->Scale(1.0f / tf1.scale);
	shape1->Rotate(-tf1.rotation);
	shape1->Move(-tf1.pos);

	shape2->Scale(1.0f / tf2.scale);
	shape2->Rotate(-tf2.rotation);
	shape2->Move(-tf2.pos);

	return colliding;
}


