#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "GLFWevi.h"
#include "GLerror.h"
#include "shader.h"
#include "PointData.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexAttribs.h"
#include "Texture.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

using namespace std;
int main(void)
{
    GLFWwindow* window = GLConstruct(1920, 1080);
    glCheckError();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    VertexArray vao;

    VertexBuffer vbo(cubevertices, sizeof(cubevertices));

    VertexAttrib posvat = { 0, 3, GL_FLOAT, GL_FALSE }; // location, dim, type, normalized
    VertexAttrib texposvat = { 1, 2, GL_FLOAT, GL_FALSE };
    vector<VertexAttrib> vats = { posvat, texposvat };
    VertexAttribs vatso(vats);

    IndexBuffer ibo(cubeindices, sizeof(cubeindices) / sizeof(cubeindices[0]));

    glm::mat4 proj;
    proj = glm::perspective<float>(glm::radians(45.0f), 1920.0 / 1080.0, 0.01f, 100.0f);

    Shader shader("src/shaders/shader.glsl"); //the parameter is the path of glsl
    shader.Bind();

    Texture texture("res/Carved_Pumpkin.png");
    Texture texture1("res/Diamond.png");
    texture.Bind();
    texture1.Bind(1);
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform1i("u_Texture1", 1);


    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
    shader.Unbind();


    Renderer renderer;

    glCheckError();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model = glm::identity<glm::mat4>();
        glm::mat4 view = glm::identity<glm::mat4>();
        float time = (float)glfwGetTime();
        model = glm::rotate(model, time * glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 0.5f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 mvp = proj * view * model;
        /* Render here */
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(vao, ibo, shader);
        GLLoopEnd(window);
    }
    GLDestruct(window);
    return 0;
}