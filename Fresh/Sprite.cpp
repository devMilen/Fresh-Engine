#include "Sprite.h"

Sprite::Sprite() {}

void Sprite::Select()
    {
	    ABO.Select();
        VBO.AssignPointer(pLoc, pflPerVertex, pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float)));
        VBO.AssignPointer(pLoc2, pflPerVertex2, pstride2 * sizeof(float), (void*)(pbeginOffset2 * sizeof(float)));
	    program.Select();
        glUniformMatrix4fv(program.ULocOf("mat"), 1, GL_FALSE, &mat[0][0]);
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
        glUniform4f(program.ULocOf("givenColor"), r, g, b, a);
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
        glUniform4f(program.ULocOf("givenColor"), r, g, b, a);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
