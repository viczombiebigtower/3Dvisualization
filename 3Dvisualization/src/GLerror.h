#pragma once
#include <GL/glew.h>
GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
void printShaderLog(unsigned int shader);
void printProgramLog(int prog);
bool checkOpenGLError();

