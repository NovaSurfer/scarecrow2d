#version 330 core
layout (location = 0) in vec2 l_pos;
layout (location = 1) in vec2 l_uv;
layout (location = 2) in int l_tileIndex;
layout (location = 3) in mat4 l_model;

out vec2 TexCoords;
flat out int TileIndex;

//uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = l_uv;
    TileIndex = l_tileIndex;
    gl_Position = projection * l_model * vec4(l_pos, 0.0, 1.0);
}