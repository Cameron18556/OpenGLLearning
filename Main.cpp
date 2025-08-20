#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


int main()
{
	//initallisation
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	GLFWwindow* window = glfwCreateWindow(800, 800, "Cool rendering window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to make the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	
	glViewport(0, 0, 800, 800);


	//vertices for the triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		-0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	};

	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
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

	//Links VBO1 to VAO1
	VAO1.LinkVBO(VBO1, 0);
	//Unbinds all to prevent accidentaly modifiying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	//while loop that keeps the window open if the x button hasnt been pressed
	while (!glfwWindowShouldClose(window))
	{
		//specify the new background colour (the background is white by defualt)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//wite the new colour to the back frame buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//change the current shader we are using
		shaderProgram.Activate();
		//bind the VAO to make it the current vertex array that gets used
		VAO1.Bind();
		//draw the triabgles
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//bring the back frame buffer to the front 
		glfwSwapBuffers(window);

		glfwPollEvents();//adds frame by frame window behaviour as far as i can tell (like resizing the window)
	}


	//end program cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
