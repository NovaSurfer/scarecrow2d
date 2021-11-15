R"(
#version 330 core

in vec2 TexCoords;
flat in uint TileIndex;
out vec4 color;

uniform sampler2DArray img_array;
uniform vec3 img_color;
//uniform int tile_index;

void main()
{
    color = vec4(img_color, 1.0) * texture(img_array, vec3(TexCoords.xy, TileIndex));
}

)"
