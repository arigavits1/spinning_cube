#include "include/VBO.h"

VBO::VBO(GLenum p_type, size_t verticesSize, float vertices[]) : type(p_type)
{
    glGenBuffers(1, &VBOid);
	use();
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}

void VBO::use()
{
    glBindBuffer(type, VBOid);
}

unsigned int VBO::GetVbo()
{
    return VBOid;
}