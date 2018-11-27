#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 proj_model;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = proj_model * vec4(vertex.xy, 0.0, 1.0);
}