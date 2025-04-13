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
//consider implement local and global space in Transform
// 
//current - Collision, Animation, UI, Sound, some tile system, Physics
// 
//TODO:
//render each shape transformed 
//render each shape with texture transformed 
//now when V workin - Collisions

Transform transform(300, 300, 0, 2, 1);
Shape::Circle shape(100);
Sprite shapeSprite(Transform::VerticesFor(shape), Transform::IndicesFor(shape),
	true, matOffV, colScaleRotCirF, "", false, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT));

void Start() {}

void Update()
{
	transform.pos += glm::vec2(50.0f * Time::dt, 0);
	transform.rotation += -0.5f;
	shapeSprite.RenderCir(1, 1, 0, 1, shape.r, 50, transform);
}

