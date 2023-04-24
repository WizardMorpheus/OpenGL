#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../libraries/include/stb/stb_image.h"

#include "../Headers/ShaderClass.h"
#include "../Headers/VAO.h"
#include "../Headers/VBO.h"
#include "../Headers/EBO.h"
#include "../Headers/Texture.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_NAME		"yeeeees"

// Vertices coordinates
GLfloat vertices[] =
{ //   COORDINATES       /     COLORS         //
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // upper left corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // upper right
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f  // lower right
};

// Indices for vertices order
GLuint indeces[] =
{
	0,2,1,
	0,3,2
};

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

	////	sets the clear colout of glad to be a navy blue
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	////	clears the back buffer with the colour buffer bit we just set
	//glClear(GL_COLOR_BUFFER_BIT);
	////	swaps the buffers to dislay the screen.
	//glfwSwapBuffers(window);

	//	creates a shder program using the vertex and fragment shaders located in the given files.
	Shader shader_program(".\\Resources\\shaders\\default.vert", ".\\Resources\\shaders\\default.frag");

	// creates a VAO and binds it.
	VAO VAO1;
	VAO1.Bind();

	//	creates a VBO based off of the vertices array
	VBO VBO1(vertices, sizeof(vertices));
	//	creates an EBO based off of the indeces array
	EBO EBO1(indeces, sizeof(indeces));

	//	links the VAO to the VBO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//	unbinds all three so that we dont accidentally change them later.
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();


	//get the locations of uniforms
	GLuint uni_scale = glGetUniformLocation(shader_program.ID, "scale");



	//texture

	/*int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("../Resources/Textures/pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint uni_tex0 = glGetUniformLocation(shader_program.ID, "tex0");
	shader_program.Activate();
	glUniform1i(uni_tex0, 0);*/


	// Texture
	Texture popCat("E:\\Programming\\Visual_Studio\\Projects\\OpenGL\\OpenGL\\Resources\\textures\\pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader_program, "tex0", 0);



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

		//set the the uniforms
		glUniform1f(uni_scale, 1.5f);
		popCat.Bind();



		//	binds the VAO
		VAO1.Bind();
		//	draws the elements in the VAO
		glDrawElements(GL_TRIANGLES,sizeof(indeces)/sizeof(indeces[0]), GL_UNSIGNED_INT, 0);
		//	swaps the buffers so that the resulting image is displayed.
		glfwSwapBuffers(window);

	}


	//	deletes the VAO, VBO, EBO and shader program so as  to not leak memory
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader_program.Delete();
	popCat.Delete();
	//	destroys the window and teminate GLFW before quit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
