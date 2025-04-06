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
Shape::Pentagon pent(300, 200, 300+100, 200+137.5);

void Start()
{
    std::array<float, 10> vertices = {
        pent.A.x, pent.A.y,
        pent.B.x, pent.B.y,
        pent.C.x, pent.C.y,
        pent.D.x, pent.D.y,
        pent.E.x, pent.E.y
    };

    std::array<unsigned int, 9> indices = {
        0, 1, 4,
        1, 2, 4,
        4, 2, 3
    };

    sprite = Sprite(vertices, indices, true, matOffV, colF, "", false, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    sprite.Render(1, 1, 0, 1);
}

