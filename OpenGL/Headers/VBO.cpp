#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//	generates a Vertex Buffer and assigns it to VBO
	glGenBuffers(1, &ID);
	//	binds the Vertex Buffer to the context?
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//	sets the Vertex buffer data to be the vertices array created earlier.
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
