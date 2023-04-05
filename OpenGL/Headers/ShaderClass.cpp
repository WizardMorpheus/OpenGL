#include "ShaderClass.h"

std::string get_file_contents(const char* filename)
{
	//	attempts to open the file at filename as an ifstream
	std::ifstream in(filename, std::ios::binary);
	//	checks if the file opened sucessfully, throws an error otherwise.
	if (in)
	{
		//	moves to the end of the file so that we can read the final position and thus get the size.
		std::string contents;
		in.seekg(0, std::ios::end);
		//	sets the size
		contents.resize(in.tellg());
		//	returns to the beginning of the file
		in.seekg(0, std::ios::beg);
		//	reads all of the content and stores it
		in.read(&contents[0], contents.size());
		//	closes the ifstream and returns the content.
		in.close();
		return contents;
	}
	throw errno;
}

Shader::Shader(const char* vertexfile, const char* fragmentfile)
{
	//	string variables for the shader code
	std::string vertex_code = get_file_contents(vertexfile);
	std::string fragment_code = get_file_contents(fragmentfile);

	//	converts those strings into const char* 
	const char* vertex_src = vertex_code.c_str();
	const char* fragment_src = fragment_code.c_str();

	//	creates a GL vertex shader 
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//	Sets the source code for that shader to be the vertex shader source code above.
	glShaderSource(vertex_shader, 1, &vertex_src, NULL);
	//	The shader is currently not being compiled (because it is just a char* ATM, so we compile it now.
	glCompileShader(vertex_shader);

	//	Same process as above but now for the fragment shader.
	GLuint fragment_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_src, NULL);
	glCompileShader(fragment_shader);

	//	creates a shader program for GL to use
	ID = glCreateProgram();
	//	attatches the shaders to the program so that they are used when the program is called.
	//	the order here is imporant, we want to use the vertex shader first to determine the
	//	pixels that are being shaded and then use the fragment shader to colour them
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	//	links the shader program to GL
	glLinkProgram(ID);

	//	deletes the shaders, they are now a part of the shader program and so we dont need them directly.
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::Activate()
{
	//	uses the shader program
	glUseProgram(ID);
}

void Shader::Delete()
{
	//	deletes the program from memory
	glDeleteProgram(ID);
}
