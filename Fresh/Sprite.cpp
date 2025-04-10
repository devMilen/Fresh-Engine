#include "Sprite.h"

Sprite::Sprite() {}

void Sprite::Select()
{
	    ABO.Select();
	    shader.Select();
        glUniformMatrix4fv(shader.ULocOf("mat"), 1, GL_FALSE, &mat[0][0]);
	    texture.Select();
}

void Sprite::Render()
    {
	    Select();
	    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
    }
void Sprite::Render(float r, float g, float b, float a)
    {
        Select();
        glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
    }

void Sprite::RenderTri()
    {
        Select();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
void Sprite::RenderTri(float r, float g, float b, float a)
    {
        Select();
        glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

void Sprite::RenderLine(float width) 
{
    glLineWidth(width);
    Select();
    glDrawArrays(GL_LINES, 0, 2);
}
void Sprite::RenderLine(float r, float g, float b, float a, float width)
{
    glLineWidth(width);
    Select();
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glDrawArrays(GL_LINES, 0, 2);
}
void Sprite::RenderLineS(float width)
{
    glLineWidth(width);
    Select();
    glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
}
void Sprite::RenderLineS(float r, float g, float b, float a, float width) 
{
    glLineWidth(width);
    Select();
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
}

void Sprite::RenderCir(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, const glm::vec2& scale, float rotation)
{
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(shader.ULocOf("O_r_donutness"), O.x, 800 - O.y, radius, donutness);
    glUniform4f(shader.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));

    Select();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}
void Sprite::RenderCir(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, float scaleX, float scaleY, float rotation)
{
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(shader.ULocOf("O_r_donutness"), Ox, 800 - Oy, radius, donutness);
    glUniform4f(shader.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));

    Select();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}
void Sprite::RenderCir(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, float scaleX, float scaleY, float rotation)
{
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(shader.ULocOf("O_r_donutness"), O.x, 800 - O.y, radius, donutness);
    glUniform4f(shader.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));

    Select();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}
void Sprite::RenderCir(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, const glm::vec2& scale, float rotation)
{
    glUniform4f(shader.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(shader.ULocOf("O_r_donutness"), Ox, 800 - Oy, radius, donutness);
    glUniform4f(shader.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));

    Select();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}