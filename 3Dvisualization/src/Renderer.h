#pragma once

#include <GL/glew.h>

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer
{
public:
	void Clear();
	void Draw(VertexArray& vao, IndexBuffer& ibo, Shader& shader);

};