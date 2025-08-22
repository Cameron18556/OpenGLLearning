#include"VAO.h"

//constructor that ganerates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

//Links a VBO attribute with this VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	//type is the array type of the vertex array
	//numComponents is how many components are in one thing in the vertex array until you get to the next thing (eg. xyz pos is three big(three floats) and so is rgb)
	//stride is the size in bytes from the beggining of one vertex to another (in a XYZRBG vertex this would be the size of a float times 6)
	//offset is howmany bytes from the beggining of the vertex array to the data type you want so if its at the beggining its zero but if you go past two floats that are 4 bytes big its 8


	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}