//#include "UI.h"
//
//#pragma region TextBox
//const char* UI::TextBox::fontFilePath = "C:\\Users\\User\\Pictures\\Screenshots\\let.png";
//const float UI::TextBox::texW = .145f, UI::TextBox::texH = .25f;
//
//UI::TextBox::TextBox() {}
//UI::TextBox::TextBox(const glm::vec2& pos, const std::string& initText, float letterHeight, float letterWidth, float m_dist_z)
//	: pos(pos), text(initText), h(letterHeight), w(letterWidth)
//{
//	for (int i = 0; i < text.size(); i++)
//		AddLetterArgs(i);
//
//	textBatch = Sprite(vertices, m_dist_z, indices, false, texV, texF, fontFilePath, true,
//		glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), VBO_ARGS);
//}
//UI::TextBox::TextBox(float posX, float posY, const std::string& initText, float letterHeight, float letterWidth, float m_dist_z)
//	: pos(posX, posY), text(initText), h(letterHeight), w(letterWidth)
//{
//	for (int i = 0; i < text.size(); i++)
//		AddLetterArgs(i);
//
//	textBatch = Sprite(vertices, m_dist_z, indices, false, texV, texF, fontFilePath, true,
//		glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), VBO_ARGS);
//}
//
//void UI::TextBox::AddLetterArgs(unsigned int indexInText)
//{
//	vertices.reserve(16);
//	vertices.insert(vertices.end(), {
//		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
//		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1), pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1), pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
//		});
//
//	indices.reserve(6);
//	indices.insert(indices.end(), {
//			indexInText * 4, indexInText * 4 + 1, indexInText * 4 + 2, indexInText * 4 + 2, indexInText * 4 + 3, indexInText * 4
//		});
//}
//void UI::TextBox::AddLetter(char newLetter)
//{
//	text += newLetter;
//	unsigned int indexInText = text.size() - 1;
//
//	vertices.reserve(16);
//	vertices.insert(vertices.end(), {
//		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
//		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1),   pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1),	pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
//		});
//
//	indices.reserve(6);
//	indices.insert(indices.end(), {
//			indexInText * 4, indexInText * 4 + 1, indexInText * 4 + 2, indexInText * 4 + 2, indexInText * 4 + 3, indexInText * 4
//		});
//}
//void UI::TextBox::ChangeLetter(unsigned int indexInText, char newLetter)
//{
//	text[indexInText] = newLetter;
//
//	std::vector<float> temp = {
//		pos.x + w * indexInText,       pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - (text[indexInText] - 'a') / 7 * texH,
//		pos.x + w * indexInText,       pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW,		1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1),   pos.y - h,  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - ((text[indexInText] - 'a') / 7 + 1) * texH,
//		pos.x + w * (indexInText + 1),	pos.y,			  1.0f + (text[indexInText] - 'a') % 7 * texW + texW,   1.0f - (text[indexInText] - 'a') / 7 * texH,
//	};
//
//	for (int i = 0; i < temp.size(); i++)
//		vertices[16 * (indexInText)+i] = temp[i];
//}
//void UI::TextBox::RemoveLastLetter()
//{
//	text.pop_back();
//	vertices.resize(vertices.size() - 16);
//	indices.resize(indices.size() - 6);
//}
//void UI::TextBox::Render()
//{
//	textBatch.Select();
//	textBatch.ReplaceBufferesContents(vertices, indices);
//}
//void UI::TextBox::RenderNew()
//{
//	textBatch.Select();
//	textBatch.ReplaceBuffers(vertices, indices);
//}
//#pragma endregion
