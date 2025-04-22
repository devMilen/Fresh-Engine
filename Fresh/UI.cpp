#include "UI.h"
#pragma region Mouse
glm::vec2 UI::Mouse::pos(0);
UI::Action UI::Mouse::Mouse::action = UI::Action::NotPressed;

void UI::Mouse::Move(float x, float y)
{
	pos.x += x; pos.y += y;
}
void UI::Mouse::Move(const glm::vec2& v)
{
	pos += v;
}

void UI::Mouse::Set(float x, float y, Action action)
{
	pos.x = x; pos.y = y;
}
void UI::Mouse::Set(const glm::vec2& apos, Action aaction)
{
	pos = apos;
	action = aaction;
}

void UI::Mouse::Update(float x, float y, Action action);
void UI::Mouse::Update(const glm::vec2& v, Action action);
#pragma endregion

#pragma region Button
UI::Button::Button() : hitBox(nullptr), OnClick([](void* data) {}), onDown(true) {}
UI::Button::Button(const Shape::Def* hitBox, void (*OnClick)(void* data), bool onDown)
	: hitBox(const_cast<Shape::Def*>(hitBox)), OnClick(OnClick), onDown(onDown) {}

void UI::Button::Update(const glm::vec2& cursorPos, Action action)
{
	if (Collision::PinPoly(cursorPos, hitBox) && 
		(onDown && action == Action::JustPressed || 
		(!onDown) && action == Action::JustReleased))
		OnClick(nullptr);
}
void UI::Button::Update(float cursorPosX, float cursorPosY, Action action)
{
	if (Collision::PinPoly(cursorPosX, cursorPosY, hitBox) &&
		(onDown && action == Action::JustPressed ||
			(!onDown) && action == Action::JustReleased))
		OnClick(nullptr);
}
void UI::Button::Update(const Mouse& state)
{
	if (Collision::PinPoly(state.pos, hitBox) &&
		(onDown && state.action == Action::JustPressed ||
			(!onDown) && state.action == Action::JustReleased))
		OnClick(nullptr);
}


void UI::Button::Update(const glm::vec2& cursorPos, Action action, void* data)
{
	if (Collision::PinPoly(cursorPos, hitBox) &&
		(onDown && action == Action::JustPressed ||
			(!onDown) && action == Action::JustReleased))
		OnClick(data);
}
void UI::Button::Update(float cursorPosX, float cursorPosY, Action action, void* data)
{
	if (Collision::PinPoly(cursorPosX, cursorPosY, hitBox) &&
		(onDown && action == Action::JustPressed ||
			(!onDown) && action == Action::JustReleased))
		OnClick(data);
}
void UI::Button::Update(const Mouse& state, void* data)
{
	if (Collision::PinPoly(state.pos, hitBox) &&
		(onDown && state.action == Action::JustPressed ||
			(!onDown) && state.action == Action::JustReleased))
		OnClick(data);
}
#pragma endregion

#pragma region TextBox
const char* UI::TextBox::fontFilePath = "C:\\Users\\User\\Pictures\\Screenshots\\let.png";
const float UI::TextBox::texW = .145f, UI::TextBox::texH = .25f;

UI::TextBox::TextBox() {}
UI::TextBox::TextBox(const glm::vec2& pos, const std::string& initText, float letterHeight, float letterWidth)
	: pos(pos), text(initText), h(letterHeight), w(letterWidth)
{
	for (int i = 0; i < text.size(); i++)
		AddLetterArgs(i);

	textBatch = Sprite(vertices, indices, false, texV, texF, fontFilePath, true,
		glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), VBO_ARGS);
}
UI::TextBox::TextBox(float posX, float posY, const std::string& initText, float letterHeight, float letterWidth)
	: pos(posX, posY), text(initText), h(letterHeight), w(letterWidth)
{
	for (int i = 0; i < text.size(); i++)
		AddLetterArgs(i);

	textBatch = Sprite(vertices, indices, false, texV, texF, fontFilePath, true,
		glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), VBO_ARGS);
}

void UI::TextBox::AddLetterArgs(unsigned int indexInText)
{
	vertices.reserve(16);
	vertices.insert(vertices.end(), {
		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1), pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1), pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
		});

	indices.reserve(6);
	indices.insert(indices.end(), {
			indexInText * 4, indexInText * 4 + 1, indexInText * 4 + 2, indexInText * 4 + 2, indexInText * 4 + 3, indexInText * 4
		});
}
void UI::TextBox::AddLetter(char newLetter)
{
	text += newLetter;
	unsigned int indexInText = text.size() - 1;

	vertices.reserve(16);
	vertices.insert(vertices.end(), {
		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1),   pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1),	pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
		});

	indices.reserve(6);
	indices.insert(indices.end(), {
			indexInText * 4, indexInText * 4 + 1, indexInText * 4 + 2, indexInText * 4 + 2, indexInText * 4 + 3, indexInText * 4
		});
}
void UI::TextBox::ChangeLetter(unsigned int indexInText, char newLetter)
{
	text[indexInText] = newLetter;

	std::vector<float> temp = {
		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1),   pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
		pos.x + w * (indexInText + 1),	pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
	};

	for (int i = 0; i < temp.size(); i++)
		vertices[16 * (indexInText)+i] = temp[i];
}
void UI::TextBox::RemoveLastLetter()
{
	text.pop_back();
	vertices.resize(vertices.size() - 16);
	indices.resize(indices.size() - 6);
}
void UI::TextBox::Render()
{
	textBatch.Select();
	textBatch.RenderBatch(vertices, indices);
}
void UI::TextBox::RenderNew()
{
	textBatch.Select();
	textBatch.RenderBatchNew(vertices, indices);
}
#pragma endregion
