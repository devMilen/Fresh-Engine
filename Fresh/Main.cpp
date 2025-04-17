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

Transform shapeTransform(350, 600, 0, 1, 1);
Shape::Box shape(-100, 100, 0, 0);
Sprite shapeSprite(Transform::VerticesFor(shape, false), Transform::IndicesFor(shape), false,
	texV, texF, "C:/Users/User/Desktop/sprites/FlappyBirdSprites/flappy_bird_sprite_noBG.png",
	true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), 0, 2, 4, 0, 1, 2, 4, 2);

void Start() 
{
	shapeTransform.rotation += 30.0f;
}

void Update()
{
	shapeTransform.SetMat(shapeSprite.mat);
	shapeSprite.Render();
}

