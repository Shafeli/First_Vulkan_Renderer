#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(inColor, 1.0);
    gl_Position = vec4(inPosition, 0.5, 1);
}