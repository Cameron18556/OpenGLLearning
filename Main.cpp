#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"


const unsigned int  width = 800;
const unsigned int  height = 800;


int main()
{
	//initallisation
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	GLFWwindow* window = glfwCreateWindow(width, height, "Cool rendering window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to make the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	
	glViewport(0, 0, width, height);


	//vertices for the triangle
	GLfloat vertices[] =
	{
		//co ordinates			colours				tex co ords
		-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.0f, 0.8f, 0.0f,		0.92f, 0.86f, 0.76f,	2.5f, 5.0f,
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4, 
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};


	//init end
	

	//makes a shader objects with the default shaders "default.vert" and "default.frag"
	Shader shaderProgram("default.vert", "default.frag");

	//generates Aertex Array Object
	VAO VAO1;
	VAO1.Bind();

	//Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	//Links the positions in VBO1 to VAO1
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	//Links the RGB in VBO1 to VAO1
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//Unbinds all to prevent accidentaly modifiying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// texture

	Texture brick("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brick.texUnint(shaderProgram, "tex0", 0);

	// enables the depth buufer
	glEnable(GL_DEPTH_TEST);

	//makes camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//for keeping track of delta time in the loop
	double prevTime = glfwGetTime();

	//while loop that keeps the window open if the x button hasnt been pressed
	while (!glfwWindowShouldClose(window))
	{
		//finding delta time
		double crntTime = glfwGetTime();
		float deltaTime = crntTime - prevTime;
		prevTime = crntTime;

		//specify the new background colour (the background is white by defualt)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//cleans the back buffer and the depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//change the current shader we are using
		shaderProgram.Activate();

		//allow camera input
		camera.Inputs(window, deltaTime);
		//updates the camera matrix then sends that to the vertex shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		brick.Bind();
		//bind the VAO to make it the current vertex array that gets used
		VAO1.Bind();
		//draw the triabgles
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//bring the back frame buffer to the front 
		glfwSwapBuffers(window);

		glfwPollEvents();//adds frame by frame window behaviour as far as i can tell (like resizing the window)
	}


	//end program cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brick.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
