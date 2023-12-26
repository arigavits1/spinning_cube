#include "include/EBO.h"


EBO::EBO(GLenum type, size_t indicesSize, unsigned int indices[], GLenum drawType)
{
    glGenBuffers(1, &EBOid);
	use();
	glBufferData(type, indicesSize, indices, drawType);
}

void EBO::use()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid);
}

unsigned int EBO::GetEbo()
{
    return EBOid;
}