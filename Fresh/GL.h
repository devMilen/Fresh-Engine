#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assert.h>
#include <vector>
#include <array>

class GL
{
public:
	class ArrayBuffer
	{
	public:
		unsigned int id;

		ArrayBuffer();
		void Select();
	};

	class VertexBuffer
	{
	public:
		unsigned int id;
		VertexBuffer();
		VertexBuffer(const std::vector<float>& vertices, bool isStatic, 
			unsigned int location = 0, unsigned int flPerVertex = 2, unsigned int stride = 2 * sizeof(float), void* beginOffset = (void*)0);

		template<size_t size> VertexBuffer(const std::array<float, size>& vertices, bool isStatic,
			unsigned int location = 0, unsigned int flPerVertex = 2, unsigned int stride = 2 * sizeof(float), void* beginOffset = (void*)0)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices.data(), (isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
			AssignPointer(location, flPerVertex, stride, beginOffset);
		}

		void Select();
		void AssignPointer(unsigned int location, unsigned int flPerVertex, unsigned int stride, void* beginOffset);
	};

	class IndexBuffer
	{
	public:
		unsigned int id;

		IndexBuffer();
		IndexBuffer(const std::vector<unsigned int>& indices, bool isStatic);
		template<size_t size> IndexBuffer(const std::array<unsigned int, size>& indices, bool isStatic)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(float), indices.data(), (isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		}

		void Select();
	};

	class ShaderProgram
	{
	public:
		unsigned int id;

		ShaderProgram();
		ShaderProgram(const char* vertexShader, const char* fragmentShader);

		bool HaveShadersCompiled(unsigned int shaderToCheck);

		unsigned int ULocOf(const char* Uname);
		void Select();

#pragma region shaders
#define defV R"(
#version 330 core
layout(location = 0) in vec2 pos;

void main() {
	gl_Position = vec4(pos, 0.0f, 1.0f);
})"

#define defF R"(
   #version 330 core
	out vec4 pixelColor;

	void main(){
		pixelColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)"

#define matOffV R"(
	#version 330 core
	layout (location = 0) in vec2 pos;
	uniform vec2 offset = vec2(0.0);
	uniform mat4 mat;

	void main() {
		gl_Position = mat * vec4(pos + offset, 0.0f, 1.0f);
	}
)"

#define colF R"(
   #version 330 core
	out vec4 pixelColor;

	uniform vec4 givenColor;

	void main(){
		pixelColor = givenColor;
	}
)"

#define colCirF R"(
	#version 330 core
	out vec4 finalColor;
	uniform vec4 colorRGBA;

	uniform vec3 originPos_radius;
	uniform float donutness;

	void main(){
		vec2 movedAsToOriginPx = gl_FragCoord.xy - originPos_radius.xy;
		if(movedAsToOriginPx.x*movedAsToOriginPx.x + movedAsToOriginPx.y*movedAsToOriginPx.y <= originPos_radius.z*originPos_radius.z) 
		{
			if(movedAsToOriginPx.x*movedAsToOriginPx.x + movedAsToOriginPx.y*movedAsToOriginPx.y >= donutness*donutness) 
			{
				finalColor = colorRGBA;
			}
			else {
				finalColor = vec4(0.0);
			}
		}
		else {
			finalColor = vec4(0.0);
		}
	}
)"

#define texV R"(
	#version 330 core

	layout (location = 0) in vec2 pos;
	layout (location = 1) in vec2 givenTexCoord;		

	out vec2 texCoord;	
	uniform vec2 offset;
	uniform mat4 mat = mat4(
		1.0, 0.0, 0.0, 0.0,  
		0.0, 1.0, 0.0, 0.0,  
		0.0, 0.0, 1.0, 0.0,  
		0.0, 0.0, 0.0, 1.0  
	);

	void main() {
		gl_Position = mat * vec4(pos + offset, 0.0, 1.0);	
		texCoord = givenTexCoord;
	}
)"

#define texF R"(
	#version 330 core
	out vec4 finalColor;
	in vec2 texCoord;	
	uniform sampler2D ourTexture;

	void main() {
		finalColor = texture(ourTexture, texCoord);
	}
)"
#pragma endregion
	};

	class Texture
	{
	public:
		unsigned int id;

		Texture();
		Texture(const char* filePath, bool flip180);

		void GiveTextureParams(bool shouldBlurPixels);
		void Select();
#pragma region defPositions
#define POSITIONS_1    0.0f, 1.0f,
#define POSITIONS_2    1.0f, 1.0f,
#define POSITIONS_2_90 0.0f, 0.0f,
#define POSITIONS_3    1.0f, 0.0f,
#define POSITIONS_4    1.0f, 0.0f,
#define POSITIONS_5    0.0f, 0.0f,
#define POSITIONS_5_90 1.0f, 1.0f,
#define POSITIONS_6    0.0f, 1.0f
#pragma endregion
	};
};
