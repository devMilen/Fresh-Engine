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
//TODO: teeest shape and transform
//render each shape transformed 
//render each shape with texture transformed 
//                 

Transform transform(300, 300, 30, 1, 1);
Shape::Box poly(-100, -100, -100, 100, 100, 100, 100, -100);
Sprite polySprite(Transform::VerticesFor(poly), Transform::IndicesFor(poly),
	true, matOffV, colF, "", false, glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f));

void Start() 
{
	
}

void Update()
{
	transform.SetMat(polySprite.mat);
	polySprite.Render(1, 1, 0, 1);
}

