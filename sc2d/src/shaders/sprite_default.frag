R"(
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D img;
uniform vec3 img_color;

void main()
{    
    color = vec4(img_color, 1.0) * texture(img, TexCoords);
} 
)"
