#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Headers/ShaderClass.h"
#include "../Headers/VAO.h"
#include "../Headers/VBO.h"
#include "../Headers/EBO.h"

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

	//	creates a shder program using the vertex and fragment shaders located in the given files.
	Shader shader_program(".\\Resources\\default.vert", ".\\Resources\\default.frag");

	// creates a VAO and binds it.
	VAO VAO1;
	VAO1.Bind();

	//	creates a VBO based off of the vertices array
	VBO VBO1(vertices, sizeof(vertices));
	//	creates an EBO based off of the indeces array
	EBO EBO1(indeces, sizeof(indeces));

	//	links the VAO to the VBO
	VAO1.LinkVBO(VBO1, 0);
	//	unbinds all three so that we dont accidentally change them later.
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	
	//	while true loop for the window.
	while (!glfwWindowShouldClose(window))
	{
		//	polls events to make the window responsive.
		glfwPollEvents();

		//	sets the clear colout of glad to be a navy blue
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//	clears the back buffer with the colour buffer bit we just set
		glClear(GL_COLOR_BUFFER_BIT);

		//	uses the shader program
		shader_program.Activate();
		//	binds the VAO
		VAO1.Bind();
		//	draws the elements in the VAO
		glDrawElements(GL_TRIANGLES,9 ,GL_UNSIGNED_INT, 0);
		//	swaps the buffers so that the resulting image is displayed.
		glfwSwapBuffers(window);

	}


	//	deletes the VAO, VBO, EBO and shader program so as  to not leak memory
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader_program.Delete();

	//	destroys the window and teminate GLFW before quit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
