#version 410

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

uniform mat3 uModelToNDC;

layout (location = 0) out vec2 TexCoords;

void main() 
{
    gl_Position = vec4(vec2(uModelToNDC * vec3(vertex.xy, 1.0)), 0.0, 1.0);
    TexCoords = vertex.zw;
}
