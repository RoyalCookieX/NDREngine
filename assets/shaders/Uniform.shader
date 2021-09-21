#shader vertex
#version 330 core

layout(location = 0) in vec4 inPos;

void main()
{
	gl_Position = inPos;
}

#shader fragment
#version 330 core

uniform vec4 u_Col;

out vec4 FragColor;

void main()
{
	FragColor = u_Col;
}