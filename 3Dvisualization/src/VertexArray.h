#pragma once
#include <GL/glew.h>

class VertexArray
{
private:
	unsigned int m_VertexArrayID;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();

};