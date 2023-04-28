#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../Headers/ShaderClass.h"
#include "../Headers/VAO.h"
#include "../Headers/VBO.h"
#include "../Headers/EBO.h"
#include "../Headers/Texture.h"
#include "../Headers/Camera.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800
#define WINDOW_NAME		"yeeeees"

// Vertices coordinates
GLfloat vertices[] =
{ //   COORDINATES         /         COLORS             /    TexCoord     /       Normal
	 // Front
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,		 0.0f,  0.5f, -0.8f,
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		 0.0f,  0.5f, -0.8f,
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		 0.0f,  0.5f, -0.8f,

	// Right
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,		 0.8f,  0.5f,  0.0f,
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		 0.8f,  0.5f,  0.0f,
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		 0.8f,  0.5f,  0.0f,

	// Back
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,		 0.0f,  0.5f,  0.8f,
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		 0.0f,  0.5f,  0.8f,
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		 0.0f,  0.5f,  0.8f,

	// Left
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,		-0.8f,  0.5f,  0.0f,
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		-0.8f,  0.5f,  0.0f,
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		-0.8f,  0.5f,  0.0f,

	// Floor
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,

};

// Indices for vertices order
GLuint indeces[] =
{
	 0, 1, 2,
	 3, 4, 5,
	 6, 7, 8,
	 9,10,11,
	12,13,14,
	12,14,15
};



GLfloat lightVeritces[] =
{  //  COORDS  //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
};

GLuint lightIndeces[] =
{
	0,1,2,
	0,2,3,
	0,4,7,
	0,7,3,
	0,7,6,
	3,7,6,
	3,6,2,
	2,6,5,
	2,5,1,
	1,5,4,
	1,4,0,
	4,5,6,
	4,6,7
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	//	unbinds all three so that we dont accidentally change them later.
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();


	Shader lightShader(".\\Resources\\shaders\\light.vert", ".\\Resources\\shaders\\light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVeritces, sizeof(lightVeritces));
	EBO lightEBO(lightIndeces, sizeof(lightIndeces));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.UnBind();
	lightVBO.UnBind();
	lightEBO.UnBind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 PyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 PyramidModel = glm::mat4(1.0f);
	PyramidModel = glm::translate(PyramidModel, PyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shader_program.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader_program.ID, "model"), 1, GL_FALSE, glm::value_ptr(PyramidModel));
	glUniform4f(glGetUniformLocation(shader_program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader_program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	
	// Texture
	Texture popCat("..\\Resources\\textures\\brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader_program, "tex0", 0);


	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	
	glEnable(GL_DEPTH_TEST);
	
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	//	while true loop for the window.
	while (!glfwWindowShouldClose(window))
	{
		//	polls events to make the window responsive.
		glfwPollEvents();

		//	sets the clear colout of glad to be a navy blue
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//	clears the back buffer with the colour buffer bit we just set
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shader_program.Activate();
		glUniform3f(glGetUniformLocation(shader_program.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shader_program, "camMat");


		popCat.Bind();


		//	binds the VAO
		VAO1.Bind();
		//	draws the elements in the VAO
		glDrawElements(GL_TRIANGLES,sizeof(indeces)/sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Activate();
		camera.Matrix(lightShader, "camMat");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndeces) / sizeof(int), GL_UNSIGNED_INT, 0);



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