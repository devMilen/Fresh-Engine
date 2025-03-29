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
		Box(const glm::vec2 A, const glm::vec2 B, const glm::vec2 C, const glm::vec2 D);

		ShapeDefFuncsDeclaration
	};

	class AABB
	{
	public:
		glm::vec2 A, B;

		AABB();
		AABB(const glm::vec2 A, const glm::vec2 B);

		float Width();
		float Height();

		ShapeDefFuncsDeclaration
	};

	class Pentagon
	{
	public:
		glm::vec2 A, B, C, D, E;

		Pentagon();
		Pentagon(const glm::vec2 aA, const glm::vec2 B, const glm::vec2 C, const glm::vec2 D, const glm::vec2 E);

		ShapeDefFuncsDeclaration
	};

	class Polygon
	{
	public:
		std::vector<glm::vec2> points;

		Polygon();
		Polygon(const std::vector<glm::vec2>& aPoints);

		ShapeDefFuncsDeclaration
	};

	class Circle
	{
	public:
		glm::vec2 O;
		float r;

		Circle();
		Circle(const glm::vec2& O, float r);

		ShapeDefFuncsDeclaration
	};

	class Ellipse
	{
	public:
		glm::vec2 F1, F2;
		float rSum;

		Ellipse();
		Ellipse(const glm::vec2& F1, const glm::vec2& F2, float rSum);

		ShapeDefFuncsDeclaration
	};
};