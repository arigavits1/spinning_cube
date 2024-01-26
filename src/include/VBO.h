#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>

class VBO
{
public:
    VBO(GLenum p_type, size_t verticesSize, float vertices[]);
    void use();
    unsigned int GetVbo();

private:
    unsigned int VBOid;
    GLenum type;
};