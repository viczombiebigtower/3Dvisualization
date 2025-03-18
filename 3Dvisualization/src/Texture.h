#pragma once

#include <GL/glew.h>
#include <string>
using namespace std;

class Texture
{
private:
	unsigned int m_TextureID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const string& path);
	~Texture();

	void Bind(unsigned int slot=0);
	void Unbind();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }

};