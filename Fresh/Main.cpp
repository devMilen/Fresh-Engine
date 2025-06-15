#include "stb_image.h"
#include "CoreEngine.h"
#include "Entity.h"
#include <string>
#include <array>

//TODO: 1. Reuse the hitbox when creating a sprite 
//		2. make rendering easier (optional)
//		3. test the rest
//		4. make this compile
//		5. add animation intis for the new constructors

CREATEWINDOW MAIN

//Entity<Shape::AABB, 3, float, float, float, float> entity(
//	550, 700, 0, 1, 1,
//	Sprite::Type::StaticColShape,
//	0, "",
//	-200, 200, 200, -200
//);
Transform tf(550, 200, 30, 2, 1);
Shape::AABB hitbox(-200, 100, 200, -200);
Sprite spr(Sprite::Type::StaticColoredTfCir, hitbox, 0);

void Start() {
}

void Update() {
	spr.SetMat(tf);
	spr.Render(1, 0, 1, 1, 100, 0, tf);
}
