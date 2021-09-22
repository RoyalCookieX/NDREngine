#shader vertex
#version 330 core

layout(location = 0) in vec4 inPos;
layout(location = 1) in vec2 inTexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * inPos;
	v_TexCoord = inTexCoord;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * u_Color;
	FragColor = texColor;
}