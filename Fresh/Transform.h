#pragma once
#include "Shape.h"
#include <array>

#pragma region defines
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define RELEASE 0
#define PRESS 1
#define HOLD 2
#define POSITIONS_1    0.0f, 1.0f
#define POSITIONS_2    1.0f, 1.0f
#define POSITIONS_2_90 0.0f, 0.0f
#define POSITIONS_3    1.0f, 0.0f
#define POSITIONS_4    1.0f, 0.0f
#define POSITIONS_5    0.0f, 0.0f
#define POSITIONS_5_90 1.0f, 1.0f
#define POSITIONS_6    0.0f, 1.0f
#define Pi 3.141592
#define Rad 0.017453
#define Deg 57.2957795
#pragma endregion

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

	static std::array<float, 4> VerticesFor(const Shape::Line& line);
	static std::array<float, 6> VerticesFor(const Shape::Triangle& triangle);
	static std::array<float, 8> VerticesFor(const Shape::Box& box);
	static std::array<float, 8> VerticesFor(const Shape::AABB& aabb);
	static std::array<float, 10> VerticesFor(const Shape::Pentagon& pentagon);
	static std::array<float, 12> VerticesFor(const Shape::Hexagon& hexagon);
	static std::vector<float> VerticesFor(const Shape::Polygon& poly);
	static std::array<float, 8> VerticesFor(const Shape::Circle& cir);

	static std::array<float, 12> VerticesFor(const Shape::Triangle& triangle, bool rot90);
	static std::array<float, 16> VerticesFor(const Shape::Box& box, bool rot90);
	static std::array<float, 16> VerticesFor(const Shape::AABB& aabb, bool rot90);

	static std::array<unsigned int, 6> IndicesFor(const Shape::Box& box);
	static std::array<unsigned int, 6> IndicesFor(const Shape::AABB& aabb);
	static std::array<unsigned int, 9> IndicesFor(const Shape::Pentagon& pentagon);
	static std::array<unsigned int, 12> IndicesFor(const Shape::Hexagon& hexagon);
	static std::array<unsigned int, 6> IndicesFor(const Shape::Circle& cir);

	void SetMat(glm::mat4& mat);
};


