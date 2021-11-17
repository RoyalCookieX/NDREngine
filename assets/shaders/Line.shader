#vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

layout(std140) uniform Camera
{
    mat4 projection;
    mat4 view;
} camera;
uniform mat4 model;

out vec4 v_Color;

void main()
{
    gl_Position = camera.projection * camera.view * model * vec4(a_Position, 1.0);
    v_Color = a_Color;
}
#fragment
#version 330 core
in vec4 v_Color;
out vec4 f_Color;
void main()
{
    f_Color = v_Color;
}