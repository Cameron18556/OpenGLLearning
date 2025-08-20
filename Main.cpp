#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


//source code for the shaders. aka this is the actual code that runs for shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	//initallisation
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vertices for the triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right
		0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper right
		-0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper left
	};

	GLuint indices[] =
	{
		0, 3, 1,
		1, 2, 3
	};

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

	//init end

	//making vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//apply the shader code to the vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile shader
	glCompileShader(vertexShader);

	//making fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//apply the shader code to the fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile shader
	glCompileShader(fragmentShader);


	//putting both shaders into a shader program (i think the shader program is like a unity material that just wraps everything to do with rendering in one package)
	GLuint shaderProgram = glCreateProgram();
	//apply both shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//wrap up the shader program (i imagaine this is like saving or recompiling it now that the shaders are in it)
	glLinkProgram(shaderProgram);

	//delete the shaders since they are now in the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//VBO = vertex buffer object; VAO = Vertex array object
	GLuint VAO, VBO, EBO;

	//generate the VAO and VBO with only one object each
	glGenVertexArrays(1, &VAO); //IMPORTANT: VAO MUST be generated before the VBO
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//make the VAO the current vertex array by binding it
	glBindVertexArray(VAO);

	//bind the VBO as a array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//apply the array "vertices" to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//tell the VAO how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the VAO(??)
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	//specify the new background colour (the background is white by defualt)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//wite the new colour to the back frame buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//bring the back frame buffer to the front 
	glfwSwapBuffers(window);



	//while loop that keeps the window open if the x button hasnt been pressed
	while (!glfwWindowShouldClose(window))
	{
		//specify the new background colour (the background is white by defualt)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//wite the new colour to the back frame buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//change the current shader we are using
		glUseProgram(shaderProgram);
		//bind the VAO to make it the current vertex array that gets used
		glBindVertexArray(VAO);
		//draw the triabgles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//bring the back frame buffer to the front 
		glfwSwapBuffers(window);

		glfwPollEvents();//adds frame by frame window behaviour as far as i can tell (like resizing the window)
	}


	//end program cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}