#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;
		//constructor that makes the Shader Program from a vert shader and a frag shader
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
};

#endif 
