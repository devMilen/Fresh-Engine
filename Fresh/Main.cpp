#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN

Sprite sprite, sprite2;

void Start()
{
    Shape::Triangle tri(300, 200, 300, 700, 700, 700);
    Shape::Triangle tri2(300, 200, 300, 700, 700, 700);

    //tri.Scale(glm::vec2(0.5f, 0.5f));
    tri.Rotate(10);
    tri.Move(10, 1);

    tri2.Scale(glm::vec2(0.5f, 0.5f));
    tri2.Rotate(10);
    tri2.Move(100, 1);

    std::array<float, 6> vertices = {
        tri.A.x, tri.A.y,
        tri.B.x, tri.B.y,
        tri.C.x, tri.C.y
    };
    std::array<float, 6> vertices2 = {
        tri2.A.x, tri2.A.y,
        tri2.B.x, tri2.B.y,
        tri2.C.x, tri2.C.y
    };

    sprite = Sprite(vertices, true, matOffV, colF,
        "", true, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
    sprite2 = Sprite(vertices2, true, matOffV, colF,
        "", true, glm::ortho(0.0f, 800.0f, 800.0f, 0.0f));
}

void Update()
{
    sprite.RenderTri(1, 1, 0, 1);
    sprite2.RenderTri(1, 0, 0, 1);
}

