#include"Camera.h"

//camera constructor
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

//updates the camera matrix then sends that to the vertex shader
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	//initalizes matrices so they are not 0 or null
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//makes camera look in the direction described in orienation
	view = glm::lookAt(Position, Position + Orientation, Up);
	//adds perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	//outputs the camera matrix to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	//handels positional/ key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up)) * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 30.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 15.0f;
	}

	//handles looking/mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick == true)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		//stores mouse position
		double mouseX;
		double mouseY;
		//fills in mouseX and Y with the corrent current mouse pos
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}


		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));

		
	} 
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}