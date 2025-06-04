#pragma once

#include "Transform.h"
#include "Shape.h"
#include "Sprite.h"

class Bullet {
public:
	enum Type {
		None = 0, Weak, Normal, Strong
	};
	void Instansiate(const glm::vec2& tankPos, const glm::vec2& mousePos);
	void Move();
private:
	Transform tf;
	glm::vec2 dir;
	static std::array<float, 3> speeds;
	static Shape::Triangle hitbox;
	static Sprite spr;
};

class Tank {
public:
	static void Move(float x, float y);
	static void Move(const glm::vec2& v);

	static void Shoot(const glm::vec2& mousePos, Bullet::Type bulletType);

	static void Render();

	static void TakeDmg(unsigned int damage);

	static const Shape::Box& GetHitBox();

	static void Init();

	static void RecieveInput(const std::bitset<26>& buttons);

private:
	static const float m_speed;
	static unsigned int m_health;
	static std::array<float, 3> m_reload_times, m_recoid_dists;
	static Transform m_tf;
	static Shape::Box m_hitbox;
	static Sprite m_spr;
	static std::vector<Bullet> m_bullets;
};