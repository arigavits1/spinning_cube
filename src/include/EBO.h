#pragma once
#include <glad/glad.h>
#include <iostream>

class EBO
{
public:
    EBO(GLenum type, size_t indicesSize, unsigned int indices[], GLenum drawType);
    void use();
    unsigned int GetEbo();
private:
    unsigned int EBOid;
};