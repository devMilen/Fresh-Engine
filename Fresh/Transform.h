#pragma once
#include "Shape.h"

class Transform 
{
public:
	glm::vec2 pos, scale;
	float rotation;

	Transform();
	Transform(const glm::vec2& pos, float rotation, const glm::vec2& scale);
	Transform(float posX, float posY, float rotation, float scaleX, float scaleY);
	Transform(const glm::vec2& pos, float rotation, float scaleX, float scaleY);
	Transform(float posX, float posY, float rotation, const glm::vec2& scale);

	void Move(const glm::vec2& v);
	void Move(float x, float y);

	void Scale(const glm::vec2& scaler);
	void Scale(float scalerX, float scalerY);
	void SetScale(const glm::vec2& scaler);
	void SetScale(float scalerX, float scalerY);

	static glm::vec2 RotatedP(const glm::vec2& p, const glm::vec2& pivot, float degrees);
	static glm::vec2 RotatedP(float x, float y, const glm::vec2& pivot, float degrees);
	static glm::vec2 RotatedP(const glm::vec2& p, float pivotX, float pivotY, float degrees);
	static glm::vec2 RotatedP(float x, float y, float pivotX, float pivotY, float degrees);

	static glm::vec2 ScaledP(const glm::vec2& p, const glm::vec2& pivot, const glm::vec2& scaler);
	static glm::vec2 ScaledP(float x, float y, const glm::vec2& pivot, const glm::vec2& scaler);
	static glm::vec2 ScaledP(const glm::vec2& p, const glm::vec2& pivot, float scaleX, float scaleY);
	static glm::vec2 ScaledP(float x, float y, const glm::vec2& pivot, float scaleX, float scaleY);
	static glm::vec2 ScaledP(float x, float y, float pivotX, float pivotY, float scaleX, float scaleY);
	static glm::vec2 ScaledP(const glm::vec2& p, float pivotX, float pivotY, float scaleX, float scaleY);
	static glm::vec2 ScaledP(const glm::vec2& p, float pivotX, float pivotY, const glm::vec2& scale);

	std::array<float, 4> VerticesFor(const Shape::Line& line, bool isTextured, bool allVerticesFierst);
	std::array<float, 6> VerticesFor(const Shape::Triangle& triangle, bool isTextured, bool allVerticesFierst);
	std::array<float, 8> VerticesFor(const Shape::Box& box, bool isTextured, bool allVerticesFierst);
	std::array<float, 8> VerticesFor(const Shape::AABB& aabb, bool isTextured, bool allVerticesFierst);
	std::array<float, 10> VerticesFor(const Shape::Pentagon& pentagon, bool isTextured, bool allVerticesFierst);
	std::array<float, 12> VerticesFor(const Shape::Hexagon& hexagon, bool isTextured, bool allVerticesFierst);
	std::vector<float> VerticesFor(const Shape::Polygon& poly, bool isTextured, bool allVerticesFierst);
	std::array<float, 8> VerticesFor(const Shape::Circle& cir, bool isTextured, bool allVerticesFierst);

	std::array<unsigned int, 8> IndicesFor(const Shape::Box& box);
	std::array<unsigned int, 8> IndicesFor(const Shape::AABB& aabb);
	std::array<unsigned int, 10> IndicesFor(const Shape::Pentagon& pentagon);
	std::array<unsigned int, 12> IndicesFor(const Shape::Hexagon& hexagon);
	std::array<unsigned int, 8> IndicesFor(const Shape::Circle& cir);
};
