#shader vertex
#version 330 core

layout(location = 0) in vec4 inPos;
layout(location = 1) in vec4 inCol;

out vec4 v_Col;

void main()
{
	gl_Position = inPos;
	v_Col = inCol;
}

#shader fragment
#version 330 core

in vec4 v_Col;

out vec4 FragColor;

void main()
{
	FragColor = v_Col;
}