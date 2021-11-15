R"(
#version 330 core

in vec2 TexCoords;
in vec4 TexColor;
flat in uint TileIndex;

layout(location = 0) out vec4 color;

uniform sampler2D img;

void main()
{
    color = TexColor * texture(img, TexCoords);
}
)"
