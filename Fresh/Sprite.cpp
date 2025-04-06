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
