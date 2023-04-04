#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* Vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPoz.y, aPoz.z, 1.0);
}
)";

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


	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f,
		0.0f, 0.5f, 1.0f,
	};

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &Vertex_shader_src, NULL);
	glCompileShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragment_shader, 1, &Fragment_shader_src, NULL);
	glCompileShader(fragment_shader);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	
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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	//	destroys the window and teminate GLFW before quit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
