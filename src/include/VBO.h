#pragma once
#include <glad/glad.h>
#include <iostream>

class VBO
{
public:
    VBO(GLenum p_type, size_t verticesSize, float indices[]);
    void use();
    unsigned int GetVbo();

private:
    unsigned int VBOid;
    GLenum type;
};