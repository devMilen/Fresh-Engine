#pragma once
#include "assert.h"

template <typename HitBoxType, size_t animCount = 3, typename... hitBoxArgs>
class Entity {
public:
#pragma region Constructors
	inline constexpr Entity() = default;

	inline constexpr Entity(const Transform& tf, const HitBoxType& hitBox, 
		const Sprite& spr, const std::array<Animation, animCount>& animations = {}
	)
		: m_tf(tf), m_hitbox(hitBox), m_def_spr(spr), m_anims(animations) {
	}

	inline constexpr Entity(const Transform& tf, const Sprite& spr, hitBoxArgs&&... args,
		const std::array<Animation, animCount>& animations = {}
	)
		: m_tf(tf), m_hitbox(std::forward<hitBoxArgs>(args)...), m_def_spr(spr), m_anims(animations) {
	}

	inline constexpr Entity(const Transform& tf, const HitBoxType& hitBox, 
		const std::string_view& filePath, float m_dist_z, 
		const std::array<Animation, animCount>& animations = {}
	)
		: m_tf(tf), m_hitbox(hitBox), m_def_spr(TEX(m_hitbox, m_dist_z, filePath)), m_anims(animations) {
	}

	inline constexpr Entity(const Transform& tf, hitBoxArgs&&... args,
		const std::string_view& filePath, float m_dist_z, 
		const std::array<Animation, animCount>& animations = {}
	)
		: m_tf(tf), m_hitbox(std::forward<hitBoxArgs>(args)...),
		m_def_spr(TEX(m_hitbox, m_dist_z, filePath)), m_anims(animations) {
	}

	inline constexpr Entity(float posX, float posY, float rot, float scaleX, float scaleY, hitBoxArgs&&... args,
		const std::string_view& filePath, float m_dist_z, const std::initializer_list<Animation>& animations
	)
		: m_tf(posX, posY, rot, scaleX, scaleY), m_hitbox(std::forward<hitBoxArgs>(args)...),
		m_def_spr(TEX(m_hitbox, m_dist_z, filePath)), m_anims(animations) {
	}

	inline constexpr Entity(float posX, float posY, float rot, float scaleX, float scaleY,
		Sprite::Type type, float m_dist_z, const std::string& filePath, hitBoxArgs&&... args
	)
		: m_tf(posX, posY, rot, scaleX, scaleY), m_hitbox(std::forward<hitBoxArgs>(args)...) {
		AssignDefSpr(type, m_dist_z, filePath);
	}

	inline constexpr Entity(const Transform& tf, const HitBoxType& hitbox, Sprite::Type type, 
		float m_dist_z = 0, const std::string& filePath = ""
	)
		: m_tf(tf), m_hitbox(hitbox) {
		AssignDefSpr(type, m_dist_z, filePath);
	}
#pragma endregion

#pragma region Transformations
	inline constexpr void Move(const glm::vec2& v) noexcept {
		m_tf.pos += v;
		m_hitbox.Move(v);
	}

	inline constexpr void Move(float x, float y) noexcept {
		m_tf.pos.x += x; m_tf.pos.y += y;
		m_hitbox.Move(x, y);
	}

	inline constexpr void SetPos(const glm::vec2& pos) noexcept {
		Move(pos - m_tf.pos);
	}

	inline constexpr void SetPos(float x, float y) noexcept {
		Move(
			x - m_tf.pos.x,
			y - m_tf.pos.y
		);
	}

	inline constexpr void Rotate(float degrees) {
		m_tf.rotation += degrees;
		m_hitbox.Rotate(degrees);
	}

	inline constexpr void SetRotation(float degrees) {
		m_hitbox.Rotate(degrees - m_tf.rotation);
		m_tf.rotation = degrees;
	}

	inline constexpr void Scale(const glm::vec2& scale) {
		m_tf.scale *= scale;
		m_hitbox.Scale(scale);
	}

	inline constexpr void Scale(float scaleX, float scaleY) {
		m_tf.scale.x *= scaleX; m_tf.scale.y *= scaleY;
		m_hitbox.Scale(scaleX, scaleY);
	}

	inline constexpr void SetScale(const glm::vec2& scale) {
		if (scale.x == 0.0f || scale.y == 0.0f)
			throw std::logic_error("[ERROR] scale component set to 0");

		m_hitbox.Scale( scale / m_tf.scale );
		m_tf.scale = scale;
	}

	inline constexpr void SetScale(float scaleX, float scaleY) {
		if (scaleX == 0.0f || scaleY == 0.0f)
			throw std::logic_error("[ERROR] scale component set to 0");

		m_hitbox.Scale(
			scaleX / m_tf.scale.x, 
			scaleY / m_tf.scale.y
		);
		m_tf.scale.x = scaleX; m_tf.scale.y = scaleY;
	}

	inline constexpr void SetAnim(const std::array<Animation, animCount>& anims) {
		m_anims = anims;
	}

	inline constexpr void SetAnim(unsigned int index, const Animation& anim) {
		if (index >= m_anims.size())
			throw std::out_of_range("index out of the bounds of the array");

		m_anims[index] = anim;
	}

	inline constexpr void RenderDefSpr() const {
		m_def_spr.Render();
	}

	inline constexpr void RenderDefSpr(float r, float g, float b, float a) {
		m_def_spr.Render(r, g, b, a);
	}

	inline constexpr void SetCurAnim(unsigned int index) {
		m_cur_anim_index = index;
	}

	inline constexpr void NextAnim() noexcept {
		m_cur_anim_index++;

		if (m_cur_anim_index == 0 || m_cur_anim_index >= m_anims.size())
			m_cur_anim_index = 1;
	}

	inline constexpr void SetMat() {
		m_tf.SetMat(m_def_spr.m_mat);
	}
#pragma endregion

#pragma region Getters
	inline constexpr Transform& GetTF() noexcept {
		return m_tf;
	}

	inline constexpr const HitBoxType& GetHitBox() const noexcept {
		return m_hitbox;
	}

	inline constexpr Sprite& GetSprite() noexcept {
		return m_def_spr;
	}

	inline constexpr void GetCurAnimFrame() const {
		return m_anims[m_cur_anim_index];
	}

	inline constexpr void GetAnimFrameAt(unsigned int index) const {
		return m_anims[index];
	}

	inline constexpr const std::array<Animation, animCount>& GetAnims() const noexcept {
		return m_anims;
	}
#pragma endregion

private:
	Transform m_tf;
	HitBoxType m_hitbox;
	Sprite m_def_spr;
	std::array<Animation, animCount> m_anims;
	unsigned int m_cur_anim_index;

	inline void AssignDefSpr(Sprite::Type type, float m_dist_z, const std::string& filePath) {
		switch (type) {
		case Sprite::Type::ColShape:
			m_def_spr = Sprite(COL_SHAPE(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::StaticColShape:
			m_def_spr = Sprite(STATIC_COL_SHAPE(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::ColCir:
			m_def_spr = Sprite(COL_CIR(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::StaticColCir:
			m_def_spr = Sprite(STATIC_COL_CIR(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::ColTri:
			m_def_spr = Sprite(COL_TRI(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::StaticColTri:
			m_def_spr = Sprite(STATIC_COL_TRI(m_hitbox, m_dist_z));
			break;
		case Sprite::Type::Tex:
			m_def_spr = Sprite(TEX(m_hitbox, m_dist_z, filePath.c_str()));
			break;
		case Sprite::Type::StaticTex:
			m_def_spr = Sprite(STATIC_TEX(m_hitbox, m_dist_z, filePath.c_str()));
			break;
		default:
			throw std::invalid_argument("[ERROR] construction of sprite type None or unknown");
			break;
		}
	}
};
