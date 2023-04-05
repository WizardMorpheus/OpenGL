#include "EBO.h"

EBO::EBO(GLuint* indeces, GLsizeiptr size)
{
	//	generates a Vertex Buffer and assigns it to VBO
	glGenBuffers(1, &ID);
	//	binds the Vertex Buffer to the context?
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//	sets the Vertex buffer data to be the vertices array created earlier.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
