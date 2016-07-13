#include <Engine/Rendering/Texture.h>
#include "Rendering/glew.h"
#include <gl/GL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
Texture* Texture::LoadTexture(char* filename)
{
	int x,y,n;
	uint8_t* data = stbi_load(filename, &x, &y, &n, 0);
	GLuint tex;
	GLuint format = GL_RGBA;
	if (n == 3)format = GL_RGB;
	glGenTextures(1, &tex);
	
	glBindTexture(GL_TEXTURE_2D, tex);
	//store this in the texture/material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);
	Texture* ret = new Texture;
	ret->m_handle = tex;
	ret->m_width = x;
	ret->m_height = y;
	return ret;
}
}