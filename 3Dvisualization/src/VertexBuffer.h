#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
	unsigned int m_VertexBufferID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind();
	void Unbind();

};
