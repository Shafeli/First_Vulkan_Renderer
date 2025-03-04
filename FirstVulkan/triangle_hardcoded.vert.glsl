#version 450

// B_________C
//  \       /   A:  0.0,  0.5
//   \  +  /    B: -0.5, -0.5
//    \   /     C:  0.5, -0.5
//     \ /
//      A

vec2 positions[3] = vec2[](
    vec2(0.0, 0.5),
    vec2(-0.5, -0.5),
    vec2(0.5, -0.5)
);

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(colors[gl_VertexIndex], 1.0);
    gl_Position = vec4(positions[gl_VertexIndex], 0.5, 1);
}