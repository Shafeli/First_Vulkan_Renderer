#version 450

layout(push_constant) uniform Constants
{
    mat4 objectMatrix;
    mat4 viewMatrix;
    mat4 projectionMatrix;
};

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(inPosition + vec3(0.5, 0.5, 0.5), 1.0);
    gl_Position = projectionMatrix * viewMatrix * objectMatrix * vec4(inPosition, 1);
}