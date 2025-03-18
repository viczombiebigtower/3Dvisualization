#include "shader.h"
#include "GLerror.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

Shader::Shader(const string& filepath)
    : m_Filepath(filepath), m_ShaderID(0)
{
    m_ShaderID = createShaderProgram(filepath);
}
Shader::~Shader()
{
    glDeleteProgram(m_ShaderID);
}
unsigned int Shader::createShaderProgram(const string& filepath)
{
    enum class shaderType
    {
        no = -1, vertex = 0, fragment = 1
    };
    ifstream stream(filepath);
    string line;
    stringstream ss[2];
    shaderType type = shaderType::no;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = shaderType::vertex;
            else if (line.find("fragment") != std::string::npos)
                type = shaderType::fragment;
        }
        else ss[(int)type] << line << '\n';
    }
    string vshaderStr = ss[0].str();
    string fshaderStr = ss[1].str();
    const char* vshaderSrc = vshaderStr.c_str();
    const char* fshaderSrc = fshaderStr.c_str();

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();

    int vertCompiled, fragCompiled, linked;
    glShaderSource(vShader, 1, &vshaderSrc, NULL);
    glShaderSource(fShader, 1, &fshaderSrc, NULL);
    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled == GL_FALSE)
    {
        cout << "vertex compilation failed" << endl;
        printShaderLog(vShader);
    }
    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled == GL_FALSE)
    {
        cout << "fragment compilation failed" << endl;
        printShaderLog(fShader);
    }

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    checkOpenGLError();
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
    {
        cout << "linking failed" << endl;
        printProgramLog(program);
    }

    glValidateProgram(program);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return program;
}
void Shader::Bind()
{
    glUseProgram(m_ShaderID);
}
void Shader::Unbind()
{
    glUseProgram(0);
}
void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string name)
{
    // use hashmap to cache uniform locations so that it would be fast
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_ShaderID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}
