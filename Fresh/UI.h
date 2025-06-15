#pragma once
#include <string>
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "Shape.h"
#include "stb_image.h"

class UI
{
public:
	class Button
	{
	public:
		Shape::Def* hitBox;
		Transform* tf;
		void (*OnClick)(void* data);
		bool onDown = true;
		unsigned int mouseButtonIndex;

		Button();
		Button(Shape::Def* hitBox, Transform* tf, unsigned int mouseButtonIndex, void (*OnClick)(void* data), bool onDown);

		void Update();
		void Update(void* data);
	};

	class Draggable
	{
	public:
		Shape::Def* hitBox;

		Draggable();
		Draggable(const Shape::Def* hitBox);

		void Update(const glm::vec2& cursorPos, const glm::vec2& lastCursorPos, float dt);
		void Update(float cursorPosX, float cursorPosY, float lastCursorPosX, float lastCursorPosY, float dt);
	};

	class TextBox
	{
	public:
		static const char* fontFilePath;
		static const float texW, texH;

		glm::vec2 pos;
		float h, w;

		Sprite textBatch;
		std::vector<float> vertices = {};
		std::vector<unsigned int> indices = {};

		std::string text;

		TextBox();
		TextBox(const glm::vec2& pos, const std::string& initText, float letterHeight, float letterWidth, float m_dist_z);
		TextBox(float posX, float posY, const std::string& initText, float letterHeight, float letterWidth, float m_dist_z);

		void AddLetterArgs(unsigned int indexInText);
		void AddLetter(char newLetter);
		void ChangeLetter(unsigned int indexInText, char newLetter);
		void RemoveLastLetter();
		void Render();
		void RenderNew();

		//to add
		void RemoveLetter(unsigned int indexIntext);
		void InsertLetter(unsigned int indexIntext, char letter);
	};

	class Slider
	{
	public:

	};

	class CheckBox
	{
	public:

	};

	class DropDownMenu
	{
	public:

	};
};