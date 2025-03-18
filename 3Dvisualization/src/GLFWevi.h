#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* GLConstruct(int winWidth=1920, int winHeight=1080);
void GLDestruct(GLFWwindow* window);
void GLLoopEnd(GLFWwindow* window);

