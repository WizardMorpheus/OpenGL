#include "VAO.h"

VAO::VAO()
{
	//	generates a verte array and assigns it to VAO
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO vbo, GLuint layout, GLuint num_components, GLuint type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	//	configures the VAO that we just bound so that it knows how to read the VBO
	//	Args are:	position of vertex attrib, num_vertices, type of value,
	//				only relevant if the type is and int (otherwise set to false),
	//				amount of data between each vertex, offset of where vertices begin in the array
	glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.UnBind();
}

void VAO::Bind()
{
	//	binds the Vertex array to the context?
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	//	unbinds the vertex array so that we dont accidentally change it
	glBindVertexArray(0);
}

void VAO::Delete()
{
	//	deletes the vertex array from memory
	glDeleteVertexArrays(1, &ID);
}
