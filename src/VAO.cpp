#include "include/VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &VAOid);
	use();
}

void VAO::CreateAttribArray(unsigned int index, unsigned int size, GLenum type, bool normalized, size_t stride, const void* offset)
{
    glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void VAO::use()
{
    glBindVertexArray(VAOid);
}

unsigned int VAO::GetVao()
{
    return VAOid;
}