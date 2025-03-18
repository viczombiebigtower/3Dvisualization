#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLFWevi.h"

using namespace std;
GLFWwindow* GLConstruct(int winWidth, int winHeight)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winWidth, winHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        cout << "Error!" << endl;
    }

    cout << glGetString(GL_VERSION) << endl;


    return window;
}

void GLDestruct(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
void GLLoopEnd(GLFWwindow* window)
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}
