#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include "Transform.h"
#include <iostream>
#include "Collision.h"

CREATEWINDOW(WINDOW_WIDTH, WINDOW_HEIGHT) MAIN

//GOAL: simulate shapes render them (with animations) with collisions reacting to input and UI with sound effects
//
//TODO: test collision class, then Animation class

Transform polyTF(300, 370, 0, 1, 1);
Shape::AABB poly(-100, 100, 100, -100);
Sprite polySprite(Transform::VerticesFor(poly, false), Transform::IndicesFor(poly), false, 
	texV, texF, "C:/Users/User/Desktop/sprites/FlappyBirdSprites/flappy_bird_sprite_noBG.png", 
	false, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT));

void Start()
{
}

void Update()
{
	polyTF.SetMat(polySprite.mat);
	polySprite.Render();
}

