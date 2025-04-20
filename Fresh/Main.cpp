#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include "Transform.h"
#include <iostream>
#include "Collision.h"
#include "Animation.h"
#include "Print.h"

CREATEWINDOW(WINDOW_WIDTH, WINDOW_HEIGHT) MAIN

//GOAL: simulate shapes render them (with animations) with collisions reacting to input and UI with sound effects
//
//TODO: then Animation class, Debug class - printing

Transform tf(300, 300, 0, 2, 1);
Shape::AABB birdHitBox(-200, 200, 200, -200);
Animation birdAnimation(
	Sprite(Transform::VerticesFor(birdHitBox, true), Transform::IndicesFor(birdHitBox), true, texV, texF, 
		"C:/Users/User/Desktop/sprites/2048_blocks/block_2.png", true, 
		glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), VBO_ARGS
	), 
	{ "C:/Users/User/Desktop/sprites/2048_blocks/block_2.png", "C:/Users/User/Desktop/sprites/2048_blocks/block_64.png" },
	true,
	1.0f
);

void Start() 
{
	birdAnimation.SetLooping(true);
}

float stopAt = 0.0f;

void Update()
{
	stopAt += Time::dt;
	if (stopAt >= 10) birdAnimation.Stop();

	tf.Move(40.0f * Time::dt, 0);
	tf.rotation += 1 * Time::dt;

	birdAnimation.Update(Time::dt);
	tf.SetMat(birdAnimation.sprite.mat);
	birdAnimation.sprite.Render();
}

