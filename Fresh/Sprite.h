#pragma once
#include "GL.h"

class Sprite
{
public:
    GL::ArrayBuffer ABO;
    GL::VertexBuffer VBO;
    GL::IndexBuffer EBO;
    GL::ShaderProgram program;
    GL::Texture texture;

    glm::mat4 mat;

    unsigned int pLoc, pflPerVertex, pstride, pbeginOffset,
        pLoc2, pflPerVertex2, pstride2, pbeginOffset2, indicesSize;

    Sprite();

    template <class VertexArr, class IndexArr>
    Sprite(const VertexArr& vertices, const IndexArr& indices, bool isStatic, 
        const char* vertexShader, const char* fragmentShader, const char* filePath, bool flipVerticaly = true, const glm::mat4& mat = glm::mat4(1.0),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0,
        unsigned int pLoc2 = 0, unsigned int pflPerVertex2 = 2, unsigned int pstride2 = 0, unsigned int pbeginOffset2 = 0, unsigned int indicesSize = 6
        )
        : ABO(), VBO(vertices, true), EBO(indices, isStatic), program(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat),
        pLoc(pLoc), pflPerVertex(pflPerVertex), pstride(pstride), pbeginOffset(pbeginOffset),
        pLoc2(pLoc2), pflPerVertex2(pflPerVertex2), pstride2(pstride2), pbeginOffset2(pbeginOffset2), indicesSize(indices.size())
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
        : ABO(), VBO(vertices, true), program(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat),
        pLoc(pLoc), pflPerVertex(pflPerVertex), pstride(pstride), pbeginOffset(pbeginOffset),
        pLoc2(0), pflPerVertex2(0), pstride2(0), pbeginOffset2(0), indicesSize(0)
    {
        glVertexAttribPointer(pLoc, pflPerVertex, GL_FLOAT, false, pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float)));
        glEnableVertexAttribArray(pLoc);
    }

    void Select();

    void Render();
    void Render(float r, float g, float b, float a);

    void RenderTri();
    void RenderTri(float r, float g, float b, float a);
};