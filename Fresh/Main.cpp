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
//GOAL: simulate shapes some with sprites(with animations) with collisions reacting to input and UI
// TODO: current - Shape class
//  UI, Animation, Collision, some tile system, Transform, Sound, Physics


Sprite sprite;
Shape::Line line(400, 400, 200, 300);

void Start()
{
    std::array<float, 8> vertices = {
        line.A.x,line.A.y,
        line.B.x,line.B.y,
        500, 600
    };

    std::array<unsigned int, 4> indices = {1, 0, 0, 2};

    sprite = Sprite(vertices, indices, true, matOffV, colF, "", false,
        glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
    std::cout << glGetError() << std::endl;
}

void Update()
{
    sprite.RenderLineS(0, 1, 1, 0);
}

