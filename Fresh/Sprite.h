#pragma once
#include "Transform.h"
#include "GL.h"

#define COL_SHAPE(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, Transform::IndicesFor(hitBox), false, matOffV, colF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))
#define TEX(hitBox, depth, filePath) Sprite(Transform::VerticesFor(hitBox, true), depth, Transform::IndicesFor(hitBox), false, texV, texF, filePath, true, \
glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), 0, 2, 4, 0, 1, 2, 4, 2)
#define STATIC_COL_SHAPE(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, Transform::IndicesFor(hitBox), true, matOffV, colF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))
#define STATIC_TEX(hitBox, depth, filePath) Sprite(Transform::VerticesFor(hitBox, true), depth, Transform::IndicesFor(hitBox), true, texV, texF, filePath, true, \
glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT), 0, 2, 4, 0, 1, 2, 4, 2)
#define COL_TRI(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, false, matOffV, colF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))
#define STATIC_COL_TRI(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, true, matOffV, colF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT)
#define STATIC_COL_CIR(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, Transform::IndicesFor(hitBox), true, matOffV, colScaleRotCirF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))
#define COL_CIR(hitBox, depth) Sprite(Transform::VerticesFor(hitBox), depth, Transform::IndicesFor(hitBox), false, matOffV, colScaleRotCirF, "", true, glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))

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
    float depth;

    Sprite();

    template <class VertexArr, class IndexArr>
    Sprite(const VertexArr& vertices, float depth, const IndexArr& indices, bool isStatic,
        const char* vertexShader, const char* fragmentShader, const char* filePath, bool flipVerticaly = true, const glm::mat4& mat = glm::mat4(1.0),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0,
        unsigned int pLoc2 = 0, unsigned int pflPerVertex2 = 2, unsigned int pstride2 = 0, unsigned int pbeginOffset2 = 0, unsigned int indicesSize = 6
        )
        : ABO(), VBO(vertices, true), depth(depth), EBO(indices, isStatic), shader(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat), indicesSize(indices.size())
    {
        glVertexAttribPointer(pLoc, pflPerVertex, GL_FLOAT, false, pstride * sizeof(float), (void*)(void*)(pbeginOffset * sizeof(float)));
        glEnableVertexAttribArray(pLoc);

        glVertexAttribPointer(pLoc2, pflPerVertex2, GL_FLOAT, false, pstride2 * sizeof(float), (void*)(void*)(pbeginOffset2 * sizeof(float)));
        glEnableVertexAttribArray(pLoc2);
    }

    template <class VertexArr>
    Sprite(const VertexArr& vertices, float depth, bool isStatic,
        const char* vertexShader, const char* fragmentShader, const char* filePath, bool flipVerticaly = true, const glm::mat4& mat = glm::mat4(1.0),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0
    )
        : ABO(), VBO(vertices, true), depth(depth), shader(vertexShader, fragmentShader), texture(filePath, flipVerticaly), mat(mat), indicesSize(0)
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

    void RenderCir(float r, float g, float b, float a, float radius, float donutness, const Transform& transform);
    void RenderCir(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, const Transform& transform);
    void RenderCir(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, const Transform& transform);
    void RenderCir(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f);
    void RenderCir(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f);
    void RenderCir(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f);
    void RenderCir(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f);

    void RenderBatch(const std::vector<float>& aVBO, const std::vector<unsigned int>& aIBO);
    void RenderBatchNew(const std::vector<float>& aVBO, std::vector<unsigned int>& aIBO);
};
