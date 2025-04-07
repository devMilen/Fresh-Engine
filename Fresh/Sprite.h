#pragma once
#include "GL.h"

class Sprite
{
public:
    GL::ArrayBuffer ABO;
    GL::VertexBuffer VBO;
    GL::IndexBuffer EBO;
    GL::ShaderProgram shader;
    GL::Texture texture;
    glm::mat4 mat;
    unsigned int indicesSize;

    Sprite();

    template <class VertexArr, class IndexArr>
    Sprite(const VertexArr& vertices, const IndexArr& indices, bool isStatic, 
        const char* vertexShader, const char* fragmentShader, const char* filePath, bool flipVerticaly = true, const glm::mat4& mat = glm::mat4(1.0),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0,
        unsigned int pLoc2 = 0, unsigned int pflPerVertex2 = 2, unsigned int pstride2 = 0, unsigned int pbeginOffset2 = 0, unsigned int indicesSize = 6
        )
        : ABO(), VBO(vertices, true), EBO(indices, isStatic), shader(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat), indicesSize(indices.size())
    {
        glVertexAttribPointer(pLoc, pflPerVertex, GL_FLOAT, false, pstride * sizeof(float), (void*)(void*)(pbeginOffset * sizeof(float)));
        glEnableVertexAttribArray(pLoc);

        glVertexAttribPointer(pLoc2, pflPerVertex2, GL_FLOAT, false, pstride2 * sizeof(float), (void*)(void*)(pbeginOffset2 * sizeof(float)));
        glEnableVertexAttribArray(pLoc2);
    }

    template <class VertexArr>
    Sprite(const VertexArr& vertices, bool isStatic,
        const char* vertexShader, const char* fragmentShader, const char* filePath, bool flipVerticaly = true, const glm::mat4& mat = glm::mat4(1.0),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0
    )
        : ABO(), VBO(vertices, true), shader(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat), indicesSize(0)
    {
        glVertexAttribPointer(pLoc, pflPerVertex, GL_FLOAT, false, pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float)));
        glEnableVertexAttribArray(pLoc);
    }

    void Select();

    void Render();
    void Render(float r, float g, float b, float a);

    void RenderTri();
    void RenderTri(float r, float g, float b, float a);

    void RenderLine(float width = 1.0f);
    void RenderLine(float r, float g, float b, float a, float width = 1.0f);
    void RenderLineS(float width = 1.0f);
    void RenderLineS(float r, float g, float b, float a, float width = 1.0f);
};