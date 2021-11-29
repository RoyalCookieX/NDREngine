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

out VERTEX_OUTPUT
{
    vec2 texCoord;
    vec3 normal;  
    vec4 color;  
} v_Out;

void main()
{
    gl_Position = camera.projection * camera.view * u_Model * vec4(a_Position, 1.0);
    v_Out.texCoord = a_TexCoord;
    v_Out.normal = a_Normal;
    
    vec3 worldNormal = normalize(mat3(u_Model) * a_Normal);
    v_Out.color = vec4(worldNormal, 1.0);
}

#fragment
#version 420 core

in VERTEX_OUTPUT
{
    vec2 texCoord;
    vec3 normal; 
    vec4 color;   
} f_In;

uniform sampler2D u_Texture;

out vec4 f_Color;

void main()
{
    vec4 fragColor = f_In.color * texture2D(u_Texture, f_In.texCoord);
    if(fragColor.a < 0.001)
        discard;
    f_Color = fragColor;
}

