R"(
#version 330 core

in vec2 TexCoords;
flat in uint TileIndex;
out vec4 color;

uniform sampler2DArray image_array;
uniform vec3 spriteColor;
//uniform int tile_index;

void main()
{
    color = vec4(spriteColor, 1.0) * texture(image_array, vec3(TexCoords.xy, TileIndex));
}

)"
