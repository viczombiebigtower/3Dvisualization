#include "Renderer.h"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);

}

void Renderer::Draw(VertexArray& vao, IndexBuffer& ibo, Shader& shader)
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);//2nd, 3rd parameters are num, type of indices

}
