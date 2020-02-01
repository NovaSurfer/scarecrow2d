R"(
#version 330 core
layout (location = 0) in vec2 l_pos;
layout (location = 1) in vec2 l_uv;
layout (location = 2) in uint l_glyphid;
layout (location = 3) in mat4 l_model;

out vec2 TexCoords;
flat out uint GlyphId;
uniform mat4 projection;

void main()
{
    TexCoords = l_uv;
    GlyphId = l_glyphid;
    gl_Position = projection * l_model * vec4(l_pos, 0.0, 1.0);
}
)"
