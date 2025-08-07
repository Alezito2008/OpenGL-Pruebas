#pragma once

#include <vector>
#include <glad/glad.h>

#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_Stride;

	std::vector<VertexBufferElement> m_Elements;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count, bool normalized = false) {
		ASSERT(false);
	}

	template<>
	void Push<float>(unsigned int count, bool normalized)
	{
		m_Elements.push_back({ GL_FLOAT, count, normalized });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count, bool normalized)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, normalized });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count, bool normalized)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, normalized });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const& { return m_Stride; }
};

