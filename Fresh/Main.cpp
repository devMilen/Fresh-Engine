#include "stb_image.h"
#include "CoreEngine.h"
#include "Entity.h"
#include <array>

//TODO: 1. Reuse the hitbox when creating m_a sprite 
//		2. make rendering easier (optional)
//		3. test the rest
//		4. make this compile
//		5. add animation intis for the new constructors

CREATEWINDOW MAIN

Transform tf(550, 200, 0, 1, 1);
Shape::Circle hitbox(200);
Sprite spr(Sprite::Type::StaticColoredTfCir, hitbox, 1);

Transform tf2(570, 200, 30, .51f, .51f);
Shape::AABB hitbox2(-200, 100, 200, -200);
Sprite spr2(Sprite::Type::StaticColoredShape, hitbox2, 0);

Color col(0.0f, 1.0f, 1.0f, 1.0f);

void Start() {
	col *= 0.5f;
}

void Update() {
	spr.SetMat(tf);
	spr.Render(col * 2, 100, 0, tf);

	spr2.SetMat(tf2);
	spr2.Render(SpriteColorConstants::g_RED);
}
