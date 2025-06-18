#include "stb_image.h"
#include "CoreEngine.h"
#include "Entity.h"

//TODO: 1. Reuse the hitbox when creating m_a sprite 
//		2. make rendering easier (optional)
//		3. test the rest
//		4. make this compile
//		5. add animation intis for the new constructors

CREATEWINDOW MAIN

Transform tf(550, 200, 30, 2, 1);
Shape::AABB hitbox(-200, 100, 200, -200);
Sprite spr(Sprite::Type::StaticColoredTfCir, hitbox, 0);
//
constexpr Color col;
constexpr float f = std::clamp(0.5f, 0.0f, 1.0f) + 1;
constexpr float r = col.GetR();

void Start() {
}

void Update() {
	spr.SetMat(tf);
	spr.Render(SpriteColorConstants::g_CYAN, 100, 0, tf);
}
