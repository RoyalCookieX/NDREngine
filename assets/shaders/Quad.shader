#shader vertex
#version 330 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(inPosition, 0.0, 1.0);
	v_TexCoord = inTexCoord;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 f_Color;

void main()
{
	f_Color = texture2D(u_Texture, v_TexCoord);
}