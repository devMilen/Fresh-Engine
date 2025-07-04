#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL.h"
#include <iostream>

#pragma region ArrayBuffer
GL::ArrayBuffer::ArrayBuffer() 
{
	glCreateVertexArrays(1, &id);
	glBindVertexArray(id);
}
void GL::ArrayBuffer::Select() const
{
	glBindVertexArray(id);
}
#pragma endregion

#pragma region VertexBuffer
GL::VertexBuffer::VertexBuffer() {}

void GL::VertexBuffer::Select() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GL::VertexBuffer::AssignPointer(unsigned int location, unsigned int flPerVertex, unsigned int stride, void* beginOffset) const
{
	glVertexAttribPointer(location, flPerVertex, GL_FLOAT, false, stride, beginOffset);
	glEnableVertexAttribArray(location);
}
#pragma endregion

#pragma region ShaderProgram
GL::ShaderProgram::ShaderProgram() {}
GL::ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader) {
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	id = glCreateProgram();

	glAttachShader(id, vertexShaderID);
	glAttachShader(id, fragmentShaderID);
	glLinkProgram(id);

	assert(HaveShadersCompiled(vertexShaderID));
	assert(HaveShadersCompiled(fragmentShaderID));

	glUseProgram(id);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
GL::ShaderProgram::ShaderProgram(const std::string_view& vertexShader, const std::string_view& fragmentShader)
	: ShaderProgram(vertexShader.data(), fragmentShader.data()) {
}

bool GL::ShaderProgram::HaveShadersCompiled(unsigned int shaderToCheck)
{
	int  success; 
	glGetShaderiv(shaderToCheck, GL_COMPILE_STATUS, &success);
	
#ifdef _DEBUG
	char infoLog[512]; 
	if (!success)
	{
		glGetShaderInfoLog(shaderToCheck, 512, NULL, infoLog); 
		std::cout << "ERROR - Shader did NOT compile: " << infoLog << std::endl; 
	}
#endif //_DEBUG

	return success;
}

unsigned int GL::ShaderProgram::ULocOf(const char* Uname) const
{
	return glGetUniformLocation(id, Uname);
}
void GL::ShaderProgram::Select() const 
{
	glUseProgram(id);
}
#pragma endregion

#pragma region IndexBuffer
GL::IndexBuffer::IndexBuffer() {}

void GL::IndexBuffer::Select() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
#pragma endregion

#pragma region Texture
GL::Texture::Texture() {}
GL::Texture::Texture(const char* filePath, bool flip180)
{
	if (filePath == nullptr)
		filePath = "";

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	stbi_set_flip_vertically_on_load(flip180);

	int width, height, bbp;
	unsigned char* data = stbi_load(filePath, &width, &height, &bbp, 0);

	GiveTextureParams(false);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(data);
}
GL::Texture::Texture(const std::filesystem::path& filePath, bool flip180) {
	if (!std::filesystem::exists(filePath) || !std::filesystem::is_directory(filePath))
		return;
	
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	stbi_set_flip_vertically_on_load(flip180);

	int width, height, bbp;
	unsigned char* data = stbi_load(filePath.string().c_str(), &width, &height, &bbp, 0);

	GiveTextureParams(false);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(data);
}

void GL::Texture::GiveTextureParams(bool shouldBlurPixels) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (shouldBlurPixels) ? GL_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (shouldBlurPixels) ? GL_NEAREST : GL_LINEAR);
}
void GL::Texture::Select() const
{
	glBindTexture(GL_TEXTURE_2D, id);
} 
#pragma endregion