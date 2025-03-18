#pragma once
#include <vector>
using namespace std;

struct VertexAttrib
{
	unsigned int location; // the index of the generic vertex attribute
	unsigned int dim; //  1 / 2 / 3 / 4
	unsigned int type; // GL_FLOAT / GL_UNSIGNED_INT / GL_UNSIGNED_BYTE
	unsigned char normalized;
};


class VertexAttribs
{
private:
	vector<VertexAttrib> m_VertexAttribs;
	unsigned int m_Stride;

public:
	VertexAttribs(VertexAttrib vat);
	VertexAttribs(vector<VertexAttrib> vats);
	void SetAttrib();
};