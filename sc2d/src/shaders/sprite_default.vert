R"(
#version 330 core
layout (location = 0) in vec2 l_pos;
layout (location = 1) in vec2 l_uv;

out vec2 TexCoords;

uniform mat4 mvp;

void main()
{
    TexCoords = l_uv;
    gl_Position = mvp * vec4(l_pos, 0.0, 1.0);
}
)"
