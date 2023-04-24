#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO vbo, GLuint layout, GLuint num_components, GLuint type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};


#endif