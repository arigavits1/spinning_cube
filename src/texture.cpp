#include "include/texture.h"

Texture::Texture(GLenum wrapS, GLenum wrapW, GLenum minFilter, GLenum magFilter, GLenum internalFormat, GLenum format, const char* path, bool flip, GLenum p_id) :  id(p_id)
{
	glGenTextures(1, &textureid);
	use();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapW);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    stbi_set_flip_vertically_on_load(flip);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, textureid);
}

void Texture::activate()
{
    use();
    glActiveTexture(id);
}