#include "Collision.h"

Collision::F::F() : aUp(1.0f), aDown(1.0f), b(0.0f){}
Collision::F::F(float aUp, float aDown, float y) : aUp(aUp), aDown(aDown), b(b) {}

float Collision::F::Calc(float x)
{
	return aUp * x / aDown + b;
}

Collision::Info::Info() : isColliding(false), depth(0.0f), CollNormal(0.0f, 0.0f) {}
Collision::Info::Info(bool isColliding, float depth, const glm::vec2& CollNormal)
	: isColliding(isColliding), depth(depth), CollNormal(CollNormal) {};

Shape::Line Collision::Projected(const Shape::Def* shape, const Shape::Line& axis)
{
	assert(shape->Type() != Shape::Types::ShapeCircle);

	glm::vec2 axisDir = glm::normalize(axis.points[1] - axis.points[0]);
	float min = glm::dot(shape->points[0], axisDir), max = min;

	for (int i = 1; i < shape->pointsSize(); i++)
	{
		float proj = glm::dot(shape->points[i], axisDir);

		if (proj < min) min = proj;
		if (proj > max) max = proj;
	}

	return Shape::Line(axis.points[0] + axisDir * min, axis.points[0] + axisDir * max);
} 

bool Collision::Check1D(const Shape::Line& proj1, const Shape::Line& proj2)
{
    if (proj1.points[0].x == proj1.points[1].x)
    {
        float min1 = std::min(proj1.points[0].y, proj1.points[1].y),
            max1 = std::max(proj1.points[0].y, proj1.points[1].y);

        float min2 = std::min(proj2.points[0].y, proj2.points[1].y),
            max2 = std::max(proj2.points[0].y, proj2.points[1].y);
    }

	float min1 = std::min(proj1.points[0].x, proj1.points[1].x),
        max1 = std::max(proj1.points[0].x, proj1.points[1].x);

	float min2 = std::min(proj2.points[0].x, proj2.points[1].x),
        max2 = std::max(proj2.points[0].x, proj2.points[1].x);

	return std::max(min1, min2) <= std::min(max1, max2);
}
bool Collision::Check(const Shape::Def* shape, const Shape::Def* shape2)
{
    for (int i = 0; i < shape->pointsSize(); i++)
    {
        glm::vec2 edge = shape->points[(i + 1) % shape->pointsSize()] - shape->points[i];
        glm::vec2 axis = glm::normalize(glm::vec2(-edge.y, edge.x));

        Shape::Line proj1 = Projected(shape, Shape::Line(glm::vec2(0.0f), axis));
        Shape::Line proj2 = Projected(shape2, Shape::Line(glm::vec2(0.0f), axis));

        if (!Check1D(proj1, proj2))
            return false; 
    }

    for (int i = 0; i < shape2->pointsSize(); i++)
    {
        glm::vec2 edge = shape2->points[(i + 1) % shape2->pointsSize()] - shape2->points[i];
        glm::vec2 axis = glm::normalize(glm::vec2(-edge.y, edge.x));

        Shape::Line proj1 = Projected(shape, Shape::Line(glm::vec2(0.0f), axis));
        Shape::Line proj2 = Projected(shape2, Shape::Line(glm::vec2(0.0f), axis));

        if (!Check1D(proj1, proj2))
            return false; 
    }

    return true;
}
Collision::Info Collision::CheckInfo(const Shape::Def* shape, const Shape::Def* shape2)
{
    Info collisionInfo(false, 0.0f, glm::vec2(0.0f));

    float minOverlap = FLT_MAX;  
    glm::vec2 collisionNormal(0.0f, 0.0f);

    for (int i = 0; i < shape->pointsSize(); i++)
    {
        glm::vec2 edge = shape->points[(i + 1) % shape->pointsSize()] - shape->points[i];
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);

        Shape::Line proj1 = Projected(shape, Shape::Line(glm::vec2(0.0f), axis));
        Shape::Line proj2 = Projected(shape2, Shape::Line(glm::vec2(0.0f), axis));

        if (!Check1D(proj1, proj2))
            return collisionInfo;

        float overlap = std::min(proj1.points[1].x, proj2.points[1].x) - std::max(proj1.points[0].x, proj2.points[0].x);

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            collisionNormal = axis; 
        }
    }

    for (int i = 0; i < shape2->pointsSize(); i++)
    {
        glm::vec2 edge = shape2->points[(i + 1) % shape2->pointsSize()] - shape2->points[i];
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);

        Shape::Line proj1 = Projected(shape, Shape::Line(glm::vec2(0.0f), axis));
        Shape::Line proj2 = Projected(shape2, Shape::Line(glm::vec2(0.0f), axis));

        if (!Check1D(proj1, proj2))
            return collisionInfo;

        float overlap = std::min(proj1.points[1].x, proj2.points[1].x) - std::max(proj1.points[0].x, proj2.points[0].x);

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }
    collisionNormal = glm::normalize(collisionNormal);

    collisionInfo.isColliding = true;
    collisionInfo.depth = minOverlap;
    collisionInfo.CollNormal = collisionNormal;

    return collisionInfo;
}

bool Collision::Check(Shape::Def* shape, const Transform& transform1, Shape::Def* shape2, const Transform& transform2)
{
    shape->Move(transform1.pos);
    shape->Rotate(transform1.rotation);
    shape->Scale(transform1.scale);

    shape2->Move(transform2.pos);
    shape2->Rotate(transform2.rotation);
    shape2->Scale(transform2.scale);

    bool colliding =  Check(shape, shape2);

    shape->Scale(glm::vec2(1.0f) / transform1.scale);
    shape->Rotate(-transform1.rotation);
    shape->Move(-transform1.pos);

    shape2->Scale(glm::vec2(1.0f) / transform2.scale);
    shape2->Rotate(-transform2.rotation);
    shape2->Move(-transform2.pos);

    return colliding;
}
Collision::Info Collision::CheckInfo(Shape::Def* shape, const Transform& transform1, Shape::Def* shape2, const Transform& transform2) 
{
    shape->Move(transform1.pos);
    shape->Rotate(transform1.rotation);
    shape->Scale(transform1.scale);

    shape2->Move(transform2.pos);
    shape2->Rotate(transform2.rotation);
    shape2->Scale(transform2.scale);

    Info colliding = CheckInfo(shape, shape2);

    shape->Scale(glm::vec2(1.0f) / transform1.scale);
    shape->Rotate(-transform1.rotation);
    shape->Move(-transform1.pos);

    shape2->Scale(glm::vec2(1.0f) / transform2.scale);
    shape2->Rotate(-transform2.rotation);
    shape2->Move(-transform2.pos);

    return colliding;
}

bool Collision::CheckScaleCir(Shape::Def* shape, const Shape::Circle& cir, const Transform& cirTransform)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(cirTransform.pos, 0.0f));
    model = glm::rotate(model, glm::radians(cirTransform.rotation), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(cirTransform.scale * cir.r, 1.0f));

    glm::mat4 invModel = glm::inverse(model);
    const unsigned int count = shape->pointsSize();

    for (unsigned int i = 0; i < count; ++i)
    {
        glm::vec2 p1_world = shape->points[i];
        glm::vec2 p2_world = shape->points[(i + 1) % count]; // Wrap around

        glm::vec2 p1_local = glm::vec2(invModel * glm::vec4(p1_world, 0.0f, 1.0f));
        glm::vec2 p2_local = glm::vec2(invModel * glm::vec4(p2_world, 0.0f, 1.0f));

        if (glm::dot(p1_local, p1_local) <= 1.0f || glm::dot(p2_local, p2_local) <= 1.0f)
            return true;

        glm::vec2 edge = p2_local - p1_local;
        glm::vec2 toCenter = -p1_local;

        float t = glm::dot(toCenter, edge) / glm::dot(edge, edge);
        t = glm::clamp(t, 0.0f, 1.0f);

        glm::vec2 closest = p1_local + t * edge;

        if (glm::dot(closest, closest) <= 1.0f)
            return true;
    }

    return false;
}
bool Collision::CheckScaleCir(Shape::Def* shape, const Transform& shapeTransform, const Shape::Circle& cir, const Transform& cirTransform)
{
    shape->Move(shapeTransform.pos);
    shape->Rotate(shapeTransform.rotation);
    shape->Scale(shapeTransform.scale);

    bool colliding = CheckScaleCir(shape, cir, cirTransform);

    shape->Scale(glm::vec2(1.0f) / shapeTransform.scale); 
    shape->Rotate(-shapeTransform.rotation);
    shape->Move(-shapeTransform.pos);

    return colliding;
}



