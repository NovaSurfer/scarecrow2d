R"(
#version 330 core

in vec2 TexCoords;
flat in uint GlyphId;
out vec4 color;

uniform sampler2DArray img_array;
uniform vec3 img_color;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(img_array, vec3(TexCoords.xy, GlyphId)).r);
    color = vec4(img_color, 1.0f) * sampled;
}
)"
