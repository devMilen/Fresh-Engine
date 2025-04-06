//returning vectors by const&
#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

#define ShapeDefFuncsDeclaration 		\
void Move(const glm::vec2& v);\
void Move(float x, float y);\
\
glm::vec2 Center();\
\
void Rotate(const glm::vec2& pivot, float degrees);\
void Rotate(float pivotX, float pivotY, float degrees);\
void Rotate(float degrees);\
\
void Scale(const glm::vec2& scaler);\
void Scale(const glm::vec2& scaler, const glm::vec2& pivot);\
void Scale(const glm::vec2& scaler, float pivotX, float pivotY);\
void Scale(float scaleX, float scaleY);\
void Scale(float scaleX, float scaleY, const glm::vec2& pivot);\
void Scale(float scaleX, float scaleY, float pivotX, float pivotY);\
\
std::vector<glm::vec2> PToListVec();\
\
std::vector<Line> PToLineVec();

class Shape
{
public:
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

	class Line
	{
	public:
		glm::vec2 A, B;

		Line();
		Line(const glm::vec2& A, const glm::vec2& B);
		Line(float x1, float y1, float x2, float y2);

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
		
		std::vector<glm::vec2> PToListVec(); 
	};


	class Triangle
	{
	public:
		glm::vec2 A, B, C;

		Triangle();
		Triangle(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C);
		Triangle(float x1, float y1, float x2, float y2, float x3, float y3);

		ShapeDefFuncsDeclaration
	};

	class Box
	{
	public:
		glm::vec2 A, B, C, D;

		Box();
		Box(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
		Box(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D);

		ShapeDefFuncsDeclaration
	};

	class AABB
	{
	public:
		glm::vec2 A, B;

		AABB();
		AABB(float x1, float y1, float x2, float y2);
		AABB(const glm::vec2& A, const glm::vec2& B);

		float Width();
		float Height();

		ShapeDefFuncsDeclaration
	};

	class Pentagon
	{
	public:
		glm::vec2 A, B, C, D, E;

		Pentagon();
		Pentagon(float x, float y, float pivotX, float pivotY);
		Pentagon(const glm::vec2& A, const glm::vec2& pivot);
		Pentagon(float x, float y, const glm::vec2& pivot);
		Pentagon(const glm::vec2& A, float pivotX, float pivotY);
		Pentagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
		Pentagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D, const glm::vec2& E);

		ShapeDefFuncsDeclaration
	};

	class Hexagon
	{
	public:
		glm::vec2 A, B, C, D, E, F;

		Hexagon();
		Hexagon(float x1, float y1, float maxR);
		Hexagon(const glm::vec2& A, float maxR);
		Hexagon(float x1, float y1, float x2, float y2, float x3, float y3,
			float x4, float y4, float x5, float y5, float x6, float y6);
		Hexagon(const glm::vec2& aA, const glm::vec2& B, const glm::vec2& C,
			const glm::vec2& D, const glm::vec2& E, const glm::vec2& F);

		ShapeDefFuncsDeclaration
	};

	class Polygon
	{
	public:
		std::vector<glm::vec2> points;

		Polygon();
		Polygon(const std::vector<float>& aPoints);
		Polygon(const std::vector<glm::vec2>& aPoints);

		std::vector<Line> SnakePToLineVec();
		ShapeDefFuncsDeclaration
	};

	class Circle
	{
	public:
		glm::vec2 O;
		float r;

		Circle();
		Circle(float Ox, float Oy, float r);
		Circle(const glm::vec2& O, float r);

		ShapeDefFuncsDeclaration
	};

	class ScaleCir
	{
	public:

		glm::vec2 O, scale;
		float r;

		ScaleCir();
		ScaleCir(float Ox, float Oy, float r, float scaleX, float scaleY);
		ScaleCir(const glm::vec2& O, float r, float scaleX, float scaleY);
		ScaleCir(float Ox, float Oy, float r, const glm::vec2& scale);
		ScaleCir(const glm::vec2& O, float r, const glm::vec2& scale);

		ShapeDefFuncsDeclaration
	};

	class Ellipse
	{
	public:
		glm::vec2 F1, F2;
		float rSum;

		Ellipse();
		Ellipse(float F1x, float F1y, float F2x, float F2y, float rSum);
		Ellipse(const glm::vec2& F1, const glm::vec2& F2, float rSum);

		ShapeDefFuncsDeclaration
	};
};