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
	//	binds the buffer 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	//	unbinds the buffer so that we dont accidentally change it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	//	deletes the buffer from memory
	glDeleteBuffers(1, &ID);
}
