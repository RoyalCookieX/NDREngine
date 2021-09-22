#shader vertex
#version 330 core

layout(location = 0) in vec4 inPos;
layout(location = 1) in vec2 inTexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = inPos;
	v_TexCoord = inTexCoord;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	FragColor = texColor;
}