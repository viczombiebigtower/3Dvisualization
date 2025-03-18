#include <GL/glew.h>
#include <algorithm>
#include "VertexAttribs.h"

using namespace std;


VertexAttribs::VertexAttribs(VertexAttrib vat)
	:m_Stride(vat.dim * sizeof(vat.type))
{
	vector<VertexAttrib> vats = { vat };
	m_VertexAttribs = vats;
	glVertexAttribPointer(0, vat.dim, vat.type, vat.normalized, m_Stride, (void*)0);
	glEnableVertexAttribArray(0);
}

VertexAttribs::VertexAttribs(vector<VertexAttrib> vats)
	: m_Stride(0)
{	
	sort(vats.begin(), vats.end(), [](const VertexAttrib& a, const VertexAttrib& b) {
		return a.location < b.location;
		});
	m_VertexAttribs = vats;
	for (auto& elem : m_VertexAttribs)
	{
		m_Stride += elem.dim * sizeof(elem.type);
	}
	SetAttrib();
}

void VertexAttribs::SetAttrib()
{
	unsigned int offset = 0;
	for (int i = 0; i < m_VertexAttribs.size(); i++)
	{
		auto& element = m_VertexAttribs[i];
		glVertexAttribPointer(i, element.dim, element.type, element.normalized, m_Stride, (void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.dim * sizeof(element.type);
	}
}
