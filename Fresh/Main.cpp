#include "stb_image.h"
#include "CoreEngine.h"
#include "Sprite.h"
#include "Time.h"
#include "Input.h"
#include "Shape.h"
#include <iostream>
CREATEWINDOW(800, 800) MAIN

Shape::Triangle tri(300, 200, 300, 700, 700, 700);

unsigned int ABO, VBO, shader;
glm::mat4 mat;

void Start()
{
    tri.Scale(glm::vec2(0.5f, 0.5f));
    tri.Rotate(10);
    tri.Move(10, 1);
    std::array<float, 6> vertices = {
        tri.A.x, tri.A.y,
        tri.B.x, tri.B.y,
        tri.C.x, tri.C.y
    };

    glGenVertexArrays(1, &ABO);
    glBindVertexArray(ABO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    const char* vertexShader = matOffV,
        *fragmentShader = colF;

    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderID);

    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderID);

    shader = glCreateProgram();

    glAttachShader(shader, vertexShaderID);
    glAttachShader(shader, fragmentShaderID);
    glLinkProgram(shader);

    glUseProgram(shader);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);


    mat = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f);
}

void Update()
{
    glBindVertexArray(ABO);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glUseProgram(shader);  
    glUniformMatrix4fv(glGetUniformLocation(shader, "mat"), 1, GL_FALSE, &mat[0][0]);
    glUniform4f(glGetUniformLocation(shader, "givenColor"), 1, 0, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    std::cout << glGetError() << std::endl;
}

