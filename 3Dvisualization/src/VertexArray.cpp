#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}
void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArrayID);
}
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}