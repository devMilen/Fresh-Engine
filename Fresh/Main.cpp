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

void Start()
{
    Shape::Hexagon pent(300, 200, 300+100, 200+137.5);
    pent.Move(-200, 0);
    pent.Rotate(-30);

    std::array<float, 12> vertices = {
        pent.A.x, pent.A.y,
        pent.B.x, pent.B.y,
        pent.C.x, pent.C.y,
        pent.D.x, pent.D.y,
        pent.E.x, pent.E.y,
        pent.F.x, pent.F.y
    };

    std::array<unsigned int, 12> indices = {
        0, 1, 5,
        1, 2, 5,
        2, 4, 5,
        2, 3, 4
    };

    sprite = Sprite(vertices, indices, true, matOffV, colF, "", false, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    sprite.Render(0, 0, 1, 1);
}

