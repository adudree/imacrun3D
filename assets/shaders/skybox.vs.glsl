#version 300 es
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords   = aPos;
    vec4 pos    = view * vec4(aPos, 0.0);
    gl_Position = projection * vec4(pos.xyz, 1.);
}