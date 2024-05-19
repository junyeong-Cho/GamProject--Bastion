#version 410

layout(location = 0) in vec2 vTexCoord;

uniform sampler2D uTex2d;

layout (location = 0) out vec4 fFragClr;

void main() 
{
    fFragClr = texture(uTex2d, vTexCoord);
}
