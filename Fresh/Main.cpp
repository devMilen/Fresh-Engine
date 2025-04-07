#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN

//TODO: simulate shapes some with sprites(with animations) with collisions reacting to input
//    current -   

Sprite sprite;
Shape::ScaleCir cir(400, 400, 200, 1, 1.25f);

void Start()
{
    std::array<float, 8> vertices = {
        cir.O.x - cir.r * cir.scale.x, cir.O.y - cir.r * cir.scale.y,
        cir.O.x - cir.r * cir.scale.x, cir.O.y + cir.r * cir.scale.y,
        cir.O.x + cir.r * cir.scale.x, cir.O.y + cir.r * cir.scale.y,
        cir.O.x + cir.r * cir.scale.x, cir.O.y - cir.r * cir.scale.y,
    };

    std::array<unsigned int, 6> indices = {
        0, 1, 2, 2, 3, 0
    };

    sprite = Sprite(vertices, indices, true, matOffV, colScaleCir, "", false, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    glUniform3f(sprite.shader.ULocOf("origin_r"), cir.O.x, 800-cir.O.y, cir.r);
    glUniform1f(sprite.shader.ULocOf("donutness"), 0);
    glUniform2f(sprite.shader.ULocOf("scale"), cir.scale.x, cir.scale.y);
    cir.scale.y -= 0.1f * Time::dt;

    sprite.Render(0, 0, 1, 1);
}

