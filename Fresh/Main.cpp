#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include "Transform.h"
#include <iostream>

CREATEWINDOW(WINDOW_WIDTH, WINDOW_HEIGHT) MAIN

//GOAL: simulate shapes render them (with animations) with collisions reacting to input and UI with sound effects
// 
//sometime - fix full screen bug
//
//TODO:
//render each shape with texture transformed 
//now when V workin - Collisions

Transform transform(300, 500, 0, 1, 1);
Shape::AABB shape(-100, 100, 100, -100);
Sprite shapeSprite(Transform::VerticesFor(shape, false), Transform::IndicesFor(shape),
	false, texV, texF, "C:/Users/User/Desktop/sprites/2048_blocks/block_64.png",
	false, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), 0, 2, 4, 0, 1, 2, 4, 2, 12);

void Start() {}

void Update()
{
	transform.pos.x++;
	transform.rotation += -0.5f*60* Time::dt;

	transform.SetMat(shapeSprite.mat);
	shapeSprite.Render();
}

