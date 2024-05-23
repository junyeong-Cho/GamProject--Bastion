#version 410

layout (location = 0) in vec2 vVertexPosition;
layout (location = 1) in vec2 vVertexTexturePosition;

layout (location = 0) out vec2 vTexCoord;

uniform mat3 uModelToNDC;

void main() 
{
    gl_Position = vec4(vec2(uModelToNDC * vec3(vVertexPosition, 1.0)), 0.0, 1.0);
    vTexCoord = vVertexTexturePosition;
}
