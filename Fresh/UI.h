#pragma once
#include <string>
#include "Sprite.h"
#include "Collision.h"
#include "Shape.h"
#include "stb_image.h"

class UI
{
public:
	enum Action
	{
		NotPressed = 0, JustPressed = 1, Held = 2, JustReleased = 3
	};
	class Mouse
	{
	public:
		static glm::vec2 pos;
		static Action action;
	
		void static Move(float x, float y);
		void static Move(const glm::vec2& v);
			 
		void static Set(float x, float y, Action action);
		void static Set(const glm::vec2& pos, Action action);
			 
		void static Update(float x, float y, Action action);
		void static Update(const glm::vec2& v, Action action);
	};

	class Button
	{
	public:
		Shape::Def* hitBox;
		void (*OnClick)(void* data);
		bool onDown = true;

		Button();
		Button(const Shape::Def* hitBox, void (*OnClick)(void* data), bool onDown);

		void Update(const glm::vec2& cursorPos, Action action);
		void Update(float cursorPosX, float cursorPosY, Action action);
		void Update(const Mouse& state);

		void Update(const glm::vec2& cursorPos, Action action, void* data);
		void Update(float cursorPosX, float cursorPosY, Action action, void* data);
		void Update(const Mouse& state, void* data);
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
		TextBox(const glm::vec2& pos, const std::string& initText, float letterHeight, float letterWidth);
		TextBox(float posX, float posY, const std::string& initText, float letterHeight, float letterWidth);

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