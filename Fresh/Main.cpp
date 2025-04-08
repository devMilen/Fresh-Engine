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
//consider implementing an actual Shape default class like an interface and make assertion fault 
// if a function is called on a shape that should not have it implemented
// 
//move ScaledP and RotatedP to transform class
// 
// 
// 
//GOAL: simulate shapes some with sprites(with animations) with collisions reacting to input and UI with sound effects
// current - Shape class with default shape
//  next - Transform, Collision, Animation, UI, Sound, some tile system, Physics
//TODO: teeest shape class
//
// 



Sprite sprite;
Shape::Line line(400, 400, 200, 300);

void Start()
{
    line.Move(100, 100);
    line.Rotate(90);
    std::array<float, 6> vertices = {
        line.points[0].x,line.points[0].y,
        line.points[1].x,line.points[1].y,
        300, 200
    };

    std::array<unsigned int, 4> indices = {0, 1, 1, 2};

    sprite = Sprite(vertices, true, matOffV, colF, "", false,
        glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    sprite.RenderLine(0, 1, 1, 0);
}

