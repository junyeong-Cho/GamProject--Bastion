#version 410

layout(location = 0) in vec2 vTexCoord;

uniform int task;
uniform sampler2D uTex2d;

layout (location = 0) out vec4 fFragClr;

void main() 
{
    fFragClr = texture(uTex2d, vTexCoord);
    if (task == 1) 
    {
        fFragClr *= vec4(1.0f * fFragClr.w, 0.65f * fFragClr.w, fFragClr.z, 1.0f);
    } 
    else if (task == 2) 
    {
        fFragClr *= vec4(0.3f * fFragClr.x * fFragClr.w, 0.3f * fFragClr.y * fFragClr.w, fFragClr.z, 1.0f);
    }
}
