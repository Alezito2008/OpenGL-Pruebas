#include "Texture.h"
#include <iostream>
#include <stb/stb_image.h>

Texture::Texture(const std::string& path, bool flip /*= false*/,
	TextureWrapping wrap /*= TextureWrapping::Repeat*/,
	TextureFiltering filter /*= TextureFiltering::Linear*/)
{
	stbi_set_flip_vertically_on_load(flip);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (data) {
		GLenum format = (m_nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar textura " << path << std::endl;
	}

	stbi_image_free(data);

	// Repetición
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
	// Filtrado
	GLint min_filter = (filter == TextureFiltering::Linear) ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(min_filter));
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
