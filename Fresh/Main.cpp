#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN
//move ScaledP and RotatedP to transform class
// 
//GOAL: simulate shapes some with sprites(with animations) with collisions reacting to input and UI with sound effects
// current - Shape::Ellipse class (more like the shader)
//  next - Transform, mat in Sprite, Collision, Animation, UI, Sound, some tile system, Physics
//TODO: teeest shape class
//        for every shape pair contiguos shapes drawing both render them dynamicaly transforming

Sprite polySprite, debug;
Shape::Circle poly(200, 300, 100);

void Start()
{
	poly.Move(200, 0);

	std::array<float, 8> polyVertices = {
		0, 0,
		800, 0,
		800, 800,
		0, 800
	};
	std::array<unsigned int, 6> polyIndices = {
		0, 1, 2, 2, 3, 0
	};

	polySprite = Sprite(polyVertices, polyIndices, true, matOffV, colScaleRotCirF, "", false,
		glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
	polySprite.RenderCir(1, 1, 0, 1, poly.r, poly.points[0].x, poly.points[0].y, 0, 2, 1, 30);
}

