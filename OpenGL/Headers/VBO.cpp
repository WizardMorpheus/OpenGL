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
	//	binds the Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	//	unbinds the vertex buffer so that we dontt accidentally change it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	//	deletes the vertex buffer from memory.
	glDeleteBuffers(1, &ID);
}
