#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN
//const correctness
// 
//move ScaledP and RotatedP to transform class
// 
//GOAL: simulate shapes some with sprites(with animations) with collisions reacting to input and UI with sound effects
// current - Shape class with default shape
//  next - Transform, Collision, Animation, UI, Sound, some tile system, Physics
//TODO: teeest shape class
//        for every shape pair contiguos shapes drawing both render them dynamicaly transforming

Sprite polySprite;
Shape::Polygon poly({200, 100, 100, 300, 300, 300, 400, 100});

void Start()
{
	poly.Move(300, 500);
	poly.Rotate(15);

	std::array<float, 8> polyVertices = {
		poly.points[0].x, poly.points[0].y,
		poly.points[1].x, poly.points[1].y,
		poly.points[2].x, poly.points[2].y,
		poly.points[3].x, poly.points[3].y
	};
	std::array<unsigned int, 6> polyIndices = {
		0, 1, 2, 2, 3, 0
	};

	polySprite = Sprite(polyVertices, polyIndices, true, matOffV, colF, "", false,
		glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
	polySprite.Render(1, 1, 0, 1);
}

