#include"ShaderClass.h"

//reads a text file and outputs it as a string
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

//constructor that makes the Shader Program from a vert shader and a frag shader
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//read vertex file and frgament file and store them as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//convert vertexCode and fragmentCode to c strings
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//making vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//apply the shader code to the vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile shader
	glCompileShader(vertexShader);

	//making fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//apply the shader code to the fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile shader
	glCompileShader(fragmentShader);


	//putting both shaders into a shader program (i think the shader program is like a unity material that just wraps everything to do with rendering in one package)
	ID = glCreateProgram();
	//apply both shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//wrap up the shader program (i imagaine this is like saving or recompiling it now that the shaders are in it)
	glLinkProgram(ID);

	//delete the shaders since they are now in the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}