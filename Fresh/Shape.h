#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Shape
{
public:
	enum Types {
		ShapeNone = 0, ShapeDef = 1, ShapeLine = 2, ShapeTriangle = 3,
		ShapeBox = 4, ShapePentagon = 5, ShapeHexagon = 6, ShapeAABB = 7,
		ShapePolygon = 8, ShapeCircle = 9, ShapeEllipse = 10
	};

	class Def {
	public:
		glm::vec2* points = nullptr;

		void Move(const glm::vec2& v); 
		void Move(float x, float y); 
		
		glm::vec2 Center(); 
		
		void Rotate(const glm::vec2& pivot, float degrees); 
		void Rotate(float pivotX, float pivotY, float degrees); 
		void Rotate(float degrees); 
		
		void Scale(const glm::vec2& scaler); 
		void Scale(const glm::vec2& scaler, const glm::vec2& pivot); 
		void Scale(const glm::vec2& scaler, float pivotX, float pivotY); 
		void Scale(float scaleX, float scaleY); 
		void Scale(float scaleX, float scaleY, const glm::vec2& pivot); 
		void Scale(float scaleX, float scaleY, float pivotX, float pivotY); 
		
		virtual ~Def() = default;

		virtual const unsigned int pointsSize() const = 0;
		virtual const Types Type() const = 0;
	};

	class Line : public Def
	{
	public:
		Line();
		Line(const glm::vec2& A, const glm::vec2& B);
		Line(float x1, float y1, float x2, float y2);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[2];
	};

	class Triangle : public Def
	{
	public:
		Triangle();
		Triangle(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C);
		Triangle(float x1, float y1, float x2, float y2, float x3, float y3);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[3];
	};

	class Box : public Def
	{
	public:
		Box();
		Box(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D);
		Box(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[4];
	};

	class AABB : public Def
	{
	public:
		AABB();
		AABB(const glm::vec2& A, const glm::vec2& B);
		AABB(float x1, float y1, float x2, float y2);

		float Width();
		float Height();

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[2];
	};

	class Pentagon : public Def
	{
	public:
		Pentagon();
		Pentagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, 
			const glm::vec2& D, const glm::vec2& E);
		Pentagon(float x1, float y1, float x2, float y2, float x3, float y3,
			float x4, float y4, float x5, float y5);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[5];
	};

	class Hexagon : public Def
	{
	public:
		Hexagon();
		Hexagon(float x1, float y1, float pivotX, float pivotY);
		Hexagon(const glm::vec2& A, float pivotX, float pivotY);
		Hexagon(float x1, float y1, const glm::vec2& pivot);
		Hexagon(const glm::vec2& A, const glm::vec2& pivot);
		Hexagon(float x1, float y1, float x2, float y2, float x3, float y3,
			float x4, float y4, float x5, float y5, float x6, float y6);
		Hexagon(const glm::vec2& aA, const glm::vec2& B, const glm::vec2& C,
			const glm::vec2& D, const glm::vec2& E, const glm::vec2& F);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[6];
	};

	class Polygon : public Def
	{
	public:
		Polygon();
		Polygon(const std::vector<float>& aPoints);
		Polygon(const std::vector<glm::vec2>& aPoints);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		std::vector<glm::vec2> localPoints;
	};

	class Circle : public Def
	{
	public:
		float r;

		Circle();
		Circle(float Ox, float Oy, float r);
		Circle(const glm::vec2& O, float r);

		const Types Type() const override;
		const unsigned int pointsSize() const override;

	private:
		glm::vec2 localPoints[1];
	};
};

