#pragma once
#include <stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture
{
public:
    Texture(GLenum wrapS, GLenum wrapW, GLenum minFilter, GLenum magFilter, GLenum internalFormat, GLenum format, const char* path, bool flip, GLenum p_id);
    void use();
    void activate();
private:
    unsigned int textureid;
    int width, height, nrChannels;
	unsigned char* data;
    GLenum id;
};