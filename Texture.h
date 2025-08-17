#pragma once
#include <glad/glad.h>
#include <string>

enum class TextureWrapping {
	Repeat = GL_REPEAT,
	MirroredRepeat = GL_MIRRORED_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	ClampToBorder = GL_CLAMP_TO_BORDER
};

enum class TextureFiltering {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR
};

class Texture
{
private:
	unsigned int m_RendererID;
	int m_width;
	int m_height;
	int m_nrChannels;
public:
	Texture(const std::string& path, bool flip = false,
		TextureWrapping wrap = TextureWrapping::Repeat,
		TextureFiltering filter = TextureFiltering::Linear);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();
};

