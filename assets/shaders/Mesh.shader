#vertex
#version 420 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

layout(std140, binding = 0) uniform Camera
{
    mat4 projection;
    mat4 view;    
} camera;
uniform mat4 u_Model;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main()
{
    gl_Position = camera.projection * camera.view * u_Model * vec4(a_Position, 1.0);
    v_TexCoord = a_TexCoord;
    v_Normal = a_Normal;
}

#fragment
#version 420 core

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

out vec4 f_Color;

void main()
{
    f_Color = texture2D(u_Texture, v_TexCoord);
}

