#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assert.h>
#include <vector>
#include <array>

#include <string_view>
#include <filesystem>

class GL
{
public:
	class ArrayBuffer
	{
	public:
		unsigned int id;

		ArrayBuffer();
		void Select() const;
	};

	class VertexBuffer
	{
	public:
		unsigned int id;

		VertexBuffer();

		template<typename Container> 
		inline VertexBuffer(const Container& vertices, bool isStatic) {
			assert(vertices.size() >= 0 && "vertices container is empty");

			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.at(0)), vertices.data(), 
				(isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
			);
		}

		void Select() const;
		void AssignPointer(unsigned int location, unsigned int flPerVertex, unsigned int stride, void* beginOffset) const;
	};

	class IndexBuffer
	{
	public:
		unsigned int id, size;

		IndexBuffer();
		template <typename Container>
		inline IndexBuffer(const Container& indices, bool isStatic) {
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), indices.data(), 
				(isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

			size = indices.size();
		}

		void Select() const;
	};

	class ShaderProgram
	{
	public:
		unsigned int id;

		ShaderProgram();
		ShaderProgram(const char* vertexShader, const char* fragmentShader);
		ShaderProgram(const std::string_view& vertexShader, const std::string_view& fragmentShader);

		bool HaveShadersCompiled(unsigned int shaderToCheck);

		unsigned int ULocOf(const char* Uname) const;
		void Select() const;
	};

	class Texture
	{
	public:
		unsigned int id;

		Texture();
		Texture(const char* filePath, bool flip180);
		Texture(const std::filesystem::path& filePath, bool flip180);

		void GiveTextureParams(bool shouldBlurPixels);
		void Select() const;
#pragma region defReadPositions
#define POSITIONS_1    0.0f, 1.0f,
#define POSITIONS_2    1.0f, 1.0f,
#define POSITIONS_2_90 0.0f, 0.0f,
#define POSITIONS_3    1.0f, 0.0f,
#define POSITIONS_4    1.0f, 0.0f,
#define POSITIONS_5    0.0f, 0.0f,
#define POSITIONS_5_90 1.0f, 1.0f,
#define POSITIONS_6    0.0f, 1.0f

#define VBO_ARGS 0, 2, 4, 0, 1, 2, 4, 2
#pragma endregion
	};
};
