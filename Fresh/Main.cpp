#include "Transform.h"
#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
#include "Collision.h"
#include "Animation.h"
#include "Print.h"
#include "Sound.h"
#include "UI.h"
CREATEWINDOW(WINDOW_WIDTH, WINDOW_HEIGHT) MAIN

//GOAL: simulate shapes render them (with animations) with collisions reacting to input and UI with sound effects
//
//TODO:  batch rendering, UI, smooth edge shaders, Physics, Print
Transform tf(900, 500, 0, 4*1080.0f/1920.0f, 2*1);
UI::TextBox tb(0, 0, "lol", 50, 50);

void Start()
{
	//tb.AddLetter('c');
	//tb.ChangeLetter(0, 'a');
	tb.RenderNew();
}

void Update()
{
	tf.Move(10.0f * Time::dt, 0);
	tf.rotation += 20.0f * Time::dt;
	tf.SetMat(tb.textBatch.mat);

	tb.Render();
}

