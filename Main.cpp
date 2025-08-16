#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02, 1.0f);\n"
"}\n\0";

int main()
{
	//initallisation
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//specify the new background colour (the background is white by defualt)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//wite the new colour to the back buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//bring the back buffer to the front 
	glfwSwapBuffers(window);



	//while loop that keeps the window open if the x button hasnt been pressed
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//adds frame by frame window behaviour as far as i can tell (like resizing the window)
	}


	//end program cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}