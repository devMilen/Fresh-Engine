#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN

//TODO: triangle and a box independantly and test each change function and collision

Sprite sprite;
Shape::Circle cir(350, 350, 100);

void Start()
{

    std::array<float, 8> vertices = {
        cir.O.x - cir.r, cir.O.y - cir.r,
        cir.O.x - cir.r, cir.O.y + cir.r,
        cir.O.x + cir.r, cir.O.y + cir.r,
        cir.O.x + cir.r, cir.O.y - cir.r,
    };

    std::array<unsigned int, 6> indices = {
        0, 1, 2, 2, 3, 0
    };

    sprite = Sprite(vertices, indices, true, matOffV, colCirF, "", false, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    glUniform3f(sprite.shader.ULocOf("originPos_radius"), cir.O.x, 800-cir.O.y, cir.r);
    glUniform1f(sprite.shader.ULocOf("donutness"), 0);
    sprite.Render(0, 0, 1, 1);
}

