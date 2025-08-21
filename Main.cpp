#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
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
		//co ordinates			colours
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 3.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	3.0f, 3.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.f,	3.0f, 0.0f,
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
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

	//gets the id of the uniform "scale" (its stored in defualt.vertex btw)
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// texture

	Texture garfeild("gaf.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	garfeild.texUnint(shaderProgram, "tex0", 0);
	


	//while loop that keeps the window open if the x button hasnt been pressed
	while (!glfwWindowShouldClose(window))
	{
		//specify the new background colour (the background is white by defualt)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//wite the new colour to the back frame buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//change the current shader we are using
		shaderProgram.Activate();
		//assigns 0.5f to the uniform "scale" wich uniID points to NOTE: MUST BE DONE WHILE THE SHADER PROGRAM IS ACTIVE
		glUniform1f(uniID, 0.5f);
		garfeild.Bind();
		//bind the VAO to make it the current vertex array that gets used
		VAO1.Bind();
		//draw the triabgles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//bring the back frame buffer to the front 
		glfwSwapBuffers(window);

		glfwPollEvents();//adds frame by frame window behaviour as far as i can tell (like resizing the window)
	}


	//end program cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	garfeild.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
