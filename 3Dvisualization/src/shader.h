#pragma once
#include <GL/glew.h>

#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"


using namespace std;
class Shader
{
private:
	string m_Filepath;
	unsigned int m_ShaderID;
	unordered_map<string, int> m_UniformLocationCache;
public:
	Shader(const string& filepath);
	~Shader();
	void Bind();
	void Unbind();

	//Set Uniforms	
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int createShaderProgram(const string& filepath);
	int GetUniformLocation(const std::string name);


};