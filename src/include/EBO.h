#pragma once
#include <glad/glad.h>
#include <iostream>

class EBO
{
public:
    EBO(GLenum type, size_t indicesSize, unsigned int indices[], GLenum drawType);
    void use();
    unsigned int GetEbo();
    bool operator!=(const std::nullptr_t& other);
private:
    unsigned int EBOid;
};