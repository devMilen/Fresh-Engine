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
GL::VertexBuffer::VertexBuffer(const std::vector<float>& vertices, bool isStatic,
	unsigned int location, unsigned int flPerVertex, unsigned int stride, void* beginOffset)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), (isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	AssignPointer(location, flPerVertex, stride, beginOffset);
}

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

bool GL::ShaderProgram::HaveShadersCompiled(unsigned int shaderidToCheck)
{
	int  success; 
	char infoLog[512]; 
	glGetShaderiv(shaderidToCheck, GL_COMPILE_STATUS, &success);
	return success;

	//if (!success)
	//{
	//	glGetShaderInfoLog(shaderToCheck, 512, NULL, infoLog); 
	//	std::cout << "ERROR - Shader did NOT compile: " << infoLog << std::endl; 
	//}
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
GL::IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices, bool isStatic)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), (isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

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