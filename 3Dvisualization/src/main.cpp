#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>

#include "GLerror.h"
#include "Shader.h"
#include "PointData.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexAttribs.h"
#include "Texture.h"
#include "Camera.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"



using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.1f;	// time between current frame and last frame
float lastFrame = 0.0f;
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        cout << "Error!" << endl;
    }

    cout << glGetString(GL_VERSION) << endl;

    glCheckError();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    VertexArray vao;

    VertexBuffer vbo(cubeVertices, sizeof(cubeVertices));
    IndexBuffer ibo(cubeIndices, sizeof(cubeIndices) / sizeof(cubeIndices[0]));

    VertexAttrib posvat = { 0, 3, GL_FLOAT, GL_FALSE }; // location, dim, type, normalized
    VertexAttrib texposvat = { 1, 2, GL_FLOAT, GL_FALSE };
    vector<VertexAttrib> vats = { posvat, texposvat };
    VertexAttribs vatso(vats);

    VertexArray vao1;

    VertexBuffer vbo1(regularSolidVertices, sizeof(regularSolidVertices));
    IndexBuffer ibo1(regularSolidIndices, sizeof(regularSolidIndices) / sizeof(regularSolidIndices[0]));


    vector<VertexAttrib> vats1 = { posvat, texposvat };
    VertexAttribs vatso1(vats1);

    Shader shader("src/shaders/shader.glsl"); //the parameter is the path of glsl

    Texture texture("res/Carved_Pumpkin.png");
    Texture texture1("res/Diamond.png");
    texture.Bind();
    texture1.Bind(1);
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform1i("u_Texture1", 1);


    vao.Unbind();
    vao1.Unbind();
    vbo.Unbind();
    vbo1.Unbind();
    ibo.Unbind();
    ibo1.Unbind();
    shader.Unbind();


    Renderer renderer;

    glCheckError();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        processInput(window);
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model1 = glm::translate(glm::identity<glm::mat4>(), glm::vec3(2.0f + sin(currentFrame), 1.0f, -3.0f))
            * glm::rotate(glm::identity<glm::mat4>(), glm::radians(50 * currentFrame), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 model2 = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-3.0f, 4.0f, -1.0f));
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 proj = glm::perspective<float>(glm::radians(camera.m_Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f);

        glm::mat4 mvp = proj * view * model;
        glm::mat4 mvp1 = proj * view * model1;
        glm::mat4 mvp2 = proj * view * model2;

        /* Render here */
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(vao, ibo, shader);
        shader.SetUniformMat4f("u_MVP", mvp2);
        renderer.Draw(vao1, ibo1, shader);
        shader.SetUniformMat4f("u_MVP", mvp1);
        renderer.Draw(vao, ibo, shader);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
        && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UPWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
        && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWNWARD, deltaTime);
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}