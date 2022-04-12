#version 330 core

out vec4 FragColor; 

in vec3 resColor;

uniform vec3 cubeColor;

void main()
{
    vec3 result = resColor * cubeColor;

    FragColor = vec4(resColor * cubeColor, 1.0);
}