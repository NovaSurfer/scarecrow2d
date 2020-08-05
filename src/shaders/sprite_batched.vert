R"(
#version 330 core
//layout (location = 3) in uint l_tileid;
layout (location = 0) in vec2 l_pos;
layout (location = 1) in vec2 l_uv;
layout (location = 2) in vec4 l_color;

out vec2 TexCoords;
out vec4 TexColor;
//flat out uint TileIndex;

uniform mat4 proj;


void main()
{
    TexCoords = l_uv;
    TexColor = l_color;
//    TileIndex = l_tileid;
    gl_Position = proj * vec4(l_pos, 0.0, 1.0);
}
)"
