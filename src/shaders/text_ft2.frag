R"(
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2DArray image_array;
uniform vec3 spriteColor;
uniform uint glyph_id;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(image_array, vec3(TexCoords.xy, glyph_id)).r);
    color = vec4(spriteColor, 1.0f) * sampled;
}
)"
