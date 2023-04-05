#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//	The Vertex Shader program source code 
const char* Vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPoz.y, aPoz.z, 1.0);
}
)";

//	The Fragment Shader program source code
const char* Fragment_shader_src = R"(
#version 330 core
out vec4 FragColor;
void main()
{
	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}
)";


#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_NAME		"yeeeees"

int main()
{
	//	initialises GLFW
	glfwInit();
	//	hints to GLFW that we are using version 3.3 (MAJOR.MINOR)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//	hints to GLFW that we are using the core profile a.k.a not using legacy or depreciated functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//	creates a GLFWwindow called window, arguments are (width, height, name, fullscreen, idk)
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
	//	terminates if the program failed to create a GLFWwindow
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window!";
		glfwTerminate();
		return -1;
	}
	//	sets the GLFW context to the window for rendering context
	glfwMakeContextCurrent(window);

	//	loads glad 
	gladLoadGL();
	//	hints to glad that it should render within the bounds of 0,0,width,height (bottom_left, top_right)
	glad_glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//	sets the clear colout of glad to be a navy blue
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//	clears the back buffer with the colour buffer bit we just set
	glClear(GL_COLOR_BUFFER_BIT);
	//	swaps the buffers to dislay the screen.
	glfwSwapBuffers(window);


	//	An array of floats that represent the vertices of a triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, //lowerleft
		0.5f, -0.5f, 0.0f, //lowerright
		0.0f, 0.5f, 0.0f, //top

		-0.5f/2, 0.0f, 0.0f, //innerleft
		0.5f/2, 0.0f, 0.0f, //innerright
		0.0f, -0.5f, 0.0f, //innerdown
	};

	GLuint indeces[] =
	{
		0,5,3, // lowerleft triangle
		5,1,4, // lowerright triangle
		3,4,2 // top triangle
	};

	//	creates a GL vertex shader 
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//	Sets the source code for that shader to be the vertex shader source code above.
	glShaderSource(vertex_shader, 1, &Vertex_shader_src, NULL);
	//	The shader is currently not being compiled (because it is just a char* ATM, so we compile it now.
	glCompileShader(vertex_shader);

	//	Same process as above but now for the fragment shader.
	GLuint fragment_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragment_shader, 1, &Fragment_shader_src, NULL);
	glCompileShader(fragment_shader);

	//	creates a shader program for GL to use
	GLuint shader_program = glCreateProgram();
	//	attatches the shaders to the program so that they are used when the program is called.
	//	the order here is imporant, we want to use the vertex shader first to determine the
	//	pixels that are being shaded and then use the fragment shader to colour them
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	//	links the shader program to GL
	glLinkProgram(shader_program);

	//	deletes the shaders, they are now a part of the shader program and so we dont need them directly.
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	//	creating a Vertex Array Object (VAO), Vertex Buffer Object (VBO)
	//	and index buffer (EBO)
	GLuint VAO, VBO, EBO;

	//	generates a verte array and assigns it to VAO
	glGenVertexArrays(1, &VAO);
	//	generates a Vertex Buffer and assigns it to VBO
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &EBO);


	//	binds the Vertex array to the context?
	glBindVertexArray(VAO);

	//	binds the Vertex Buffer to the context?
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//	sets the Vertex buffer data to be the vertices array created earlier.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);


	//	configures the VAO that we just bound so that it knows how to read the VBO
	//	Args are:	position of vertex attrib, num_vertices, type of value,
	//				only relevant if the type is and int (otherwise set to false),
	//				amount of data between each vertex, offset of where vertices begin in the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//	now binds the array buffer and vertex buffer to 0 so that we dont accidentally change them.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//	ensure EBO is unbound after the VAO because the EBO is in the VAO and unbinding before
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	
	//	while true loop for the window.
	while (!glfwWindowShouldClose(window))
	{
		//	polls events to make the window responsive.
		glfwPollEvents();

		//	sets the clear colout of glad to be a navy blue
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//	clears the back buffer with the colour buffer bit we just set
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,9 ,GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader_program);

	//	destroys the window and teminate GLFW before quit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
