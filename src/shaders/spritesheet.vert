#version 330 core
layout (location = 0) in vec2 l_pos;
layout (location = 1) in vec2 l_uv;
layout (location = 2) in vec2 l_offset;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = l_uv;
    gl_Position = projection * model * vec4(l_pos + l_offset, 0.0, 1.0);
}