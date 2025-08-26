#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"ShaderClass.h"

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		//prevents camera jumping from input
		bool firstClick = true;

		//window width and height
		int width;
		int height;

		//the camera movement speed (if changing change in Input() too)
		float speed = 15.0f;
		//the camera look speed
		float sensitivity = 100.0f;

		//camera constructor
		Camera(int width, int height, glm::vec3 position);

		//updates the camera matrix then sends that to the vertex shader

		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window, float deltaTime);
};

#endif 