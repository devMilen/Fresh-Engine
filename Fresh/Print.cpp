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
void Print::Info(const char* message, const glm::vec2& mousePos, const std::bitset<26>& isLetterPressed,
	const std::unordered_map<int, bool>& specialKeyForIsPressed,
	const std::bitset<10>& isNumberPressed)
{
	std::cout << "-------------------Input: " << message << "-----------------------" << std::endl;
	std::cout << "mousePos: (" << mousePos.x << ", " << mousePos.y << ')' << std::endl;

	std::cout << "isLetterPressed: {" << std::endl;
	for (char i = 'a'; i <= 'z'; i++)
		if(isLetterPressed[i - 'a'])
		std::cout << (char)i;
	std::cout << "};\n";

	std::cout << "isSpecialKeyPressed: {" << std::endl;
	for (std::pair<int, bool> pair : specialKeyForIsPressed)
		if(pair.second)
			std::cout << specialKeyForIsPressed.at(pair.first) << pair.first << ", " << pair.second << std::endl;
	std::cout << "};\n";

	std::cout << "isNumberPressed: {" << std::endl;
	for (char i = '0'; i <= '9'; i++)
		if (isNumberPressed[i - '0'])
			std::cout << (char)i << ", ";
	std::cout << "};\n";
	std::cout << "-------------------END OF: " << message << "-----------------------" << std::endl;
}

void Print::Info(const char* name, const glm::vec2& mousePos, const std::array<Input::Action, 5>& buttons,
	const std::bitset<26>& isLetterPressed)
{
	std::cout << "-------------------Input: " << name << "-----------------------" << std::endl;
	std::cout << "mouse pos: (" << mousePos.x << ", " << mousePos.y << ')' << std::endl;

	std::cout << "isLetterPressed: {" << std::endl;
	for (char i = 'a'; i <= 'z'; i++)
		if (isLetterPressed[i - 'a'])
			std::cout << (char)i;
	std::cout << "};\n";

	std::cout << "buttons: {" << std::endl;
	for (int i = 0; i < buttons.size(); i++)
		std::cout << buttons[i] << ", ";
	std::cout << "};\n";
	std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;

}

