#version 330 core
out vec4 FragColor;

//inputs the color from default.vert
in vec3 color;

void main()
{

	FragColor = vec4(color, 1.0f);
}