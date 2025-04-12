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
// current - Transform vertices for Shape::Def
//  next - Collision, Animation, UI, Sound, some tile system, Physics
//TODO: teeest shape and transform
//render each shape transformed 
//render each shape with texture transformed 
//                 

Shape::Box poly(200, 200, 200, 400, 400, 400, 400, 200);
Sprite polySprite(Transform::VerticesFor(poly), Transform::IndicesFor(poly),
	true, matOffV, colF, "", false, glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f));

void Start() {}

void Update()
{
	polySprite.Render(1, 1, 0, 1);
}

