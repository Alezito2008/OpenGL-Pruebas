#pragma once
#include <glad/glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define DEBUG 1

#define ASSERT(x) if (!(x)) __debugbreak();

#if DEBUG == 1
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#else 
#define GLCall(x) x;
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const IndexBuffer&, const Shader& shader);
};
