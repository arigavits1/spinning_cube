#pragma once
#include <glad/glad.h>
#include <iostream>

class VAO
{
public:
    VAO();
    void CreateAttribArray(unsigned int index, unsigned int size, GLenum type, bool normalized, size_t stride, const void* offset);
    void use();
    unsigned int GetVao();
private:
    unsigned int VAOid;
};