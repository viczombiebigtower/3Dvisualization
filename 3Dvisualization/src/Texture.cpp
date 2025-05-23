#include "Texture.h"

#include "vendor/stb_image/stb_image.h"
Texture::Texture(const string& path)
	:m_TextureID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //Texture wrapping; s-axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //t-axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Texture Filtering; minify
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnify 

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	if (m_LocalBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);


	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
}

void Texture::Bind(unsigned int slot) // slot may be 0, 1, ..., 31
{
	glActiveTexture(GL_TEXTURE0 + slot); // active the texture unit before binding, there may be more than one texture in shader
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
