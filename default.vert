#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;


// outputs the color for the fragment shader
out vec3 color;

out vec2 texCoord;

//imports camera matrix from the main loop
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0f);
	// assigns the colors from the vertex data to color
	color = aColor;
	texCoord = aTex;
}