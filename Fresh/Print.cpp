#include "Print.h"

void Print::Info(const Animation& anim, const char* name)
{
	std::cout << "-------------------Animation: " << name << "-----------------------" << std::endl;
	std::cout << "index: " << anim.index
		<< "\ntimeSinceLastFrame: " << anim.timeSinceLastFrame
		<< "\nisPlaying: " << anim.isPlaying << "\nisLooping: " << anim.isLooping
		<< "\ndurations: { ";

	for (float dur : anim.durations)
		std::cout << dur << ", ";

	std::cout << '}' << std::endl;

	for (const GL::Texture& tex : anim.frames)
		assert(glIsTexture(tex.id));
	std::cout << "all texture ids are valid textures" << std::endl;
	std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
}
void Print::Info(const Transform& tf, const char* name)
{
	std::cout << "-------------------Transform: " << name << "-----------------------" << std::endl;
	std::cout << "pos: (" << tf.pos.x << ", " << tf.pos.y << ')' << std::endl;
	std::cout << "rotation: " << tf.rotation << std::endl;
	std::cout << "scale: (" << tf.scale.x << ", " << tf.scale.y << ')' << std::endl;
	std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
}
void Print::Info(const Sprite& sprite, const char* name)
{
	std::cout << "-------------------Sprite: " << name << "-----------------------" << std::endl;
	assert(glIsVertexArray(sprite.ABO.id) && glIsBuffer(sprite.VBO.id) &&
		glIsBuffer(sprite.EBO.id) && glIsProgram(sprite.shader.id) && glIsTexture(sprite.texture.id));
	std::cout << "all ids are valid ids" << std::endl;

	std::cout << "mat: { \n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "   (";
		for (int j = 0; j < 4; j++)
		{
			std::cout << sprite.mat[i][j];
			if (j != 3) std::cout << ", ";
		}
		std::cout << "),\n";
	}
	std::cout << "}" << std::endl;
	std::cout << "indicesSize: " << sprite.indicesSize << std::endl;
	std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;

}

void PrintVec(const glm::vec2& v, const char* name)
{
	std::cout << name << ": (" << v.x << ", " << v.y << ")" << std::endl;
}
void PrintVec(const glm::vec3& v, const char* name)
{
	std::cout << name << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}
void PrintVec(const glm::vec4& v, const char* name)
{
	std::cout << name << ": (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
}
void PrintMat(const glm::mat4& mat, const char* name)
{
	std::cout << "-------------------mat4: " << name << "-----------------------" << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "   (";
		for (int j = 0; j < 4; ++j)
		{
			std::cout << mat[i][j];
			if (j < 3) std::cout << ", ";
		}
		std::cout << "),\n";
	}
	std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
}

